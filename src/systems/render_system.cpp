#include "render_system.hpp"

RenderSystem::RenderSystem(unsigned int shader, GLFWwindow* window) {

    this->shader = shader;
    modelLocation = glGetUniformLocation(shader, "model");
    normalLocation = glGetUniformLocation(shader, "normalMatrix");
    this->window = window;
}

void RenderSystem::update(
    std::unordered_map<unsigned int,TransformComponent> &transformComponents,
    std::unordered_map<unsigned int,RenderComponent> &renderComponents) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto& [entity,renderable] : renderComponents) {
        TransformComponent& transform = transformComponents[entity];

        // 获得 model 矩阵
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, transform.position);
        model = glm::rotate(model, glm::radians(transform.eulers.z), { 0.0f, 0.0f, 1.0f });

        // 获得 normal 矩阵
        glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));

        // 更新 model 到 gpu
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        // 更新 normal matrix 到 gpu
        glUniformMatrix3fv(normalLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glUniform3fv(glGetUniformLocation(shader, "albedo"), 1, glm::value_ptr(glm::vec3(0.5f, 0.0f, 0.0f)));
        glUniform1f(glGetUniformLocation(shader, "metallic"), 0.5f);
        glUniform1f(glGetUniformLocation(shader, "roughness"), 0.5f);
        glUniform1f(glGetUniformLocation(shader, "ao"), 1.0f);
        int lightNum = 4;
        glUniform1i(glGetUniformLocation(shader, "lightNum"), 4);

        glm::vec3 lightPositions[] = {
            glm::vec3(-10.0f,  10.0f, 10.0f),
            glm::vec3( 10.0f,  10.0f, 10.0f),
            glm::vec3(-10.0f, -10.0f, 10.0f),
            glm::vec3( 10.0f, -10.0f, 10.0f),
        };
        glm::vec3 lightColors[] = {
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f)
        };

        for (int i = 0; i < lightNum; i++) {
            glUniform3fv(glGetUniformLocation(shader, ("lightPositions[" + std::to_string(i) + "]").c_str()),1, glm::value_ptr(lightPositions[i]));
            glUniform3fv(glGetUniformLocation(shader, ("lightColors[" + std::to_string(i) + "]").c_str()),1, glm::value_ptr(lightColors[i]));
        }


        // 绑定唯一的材质到 slot 0
        // TODO: 设置多个材质槽位
        glBindTexture(GL_TEXTURE_2D, renderable.material);
        // 绑定 vao 后渲染
        glBindVertexArray(renderable.VAO);
        glDrawArrays(GL_TRIANGLES, 0, renderable.vertexCount);
    }
    glfwSwapBuffers(window);
}