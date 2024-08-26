#include "render_system.hpp"

RenderSystem::RenderSystem(unsigned int shader, GLFWwindow* window) {

    modelLocation = glGetUniformLocation(shader, "model");
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
        model = glm::rotate(
            model, glm::radians(transform.eulers.z),
            { 0.0f, 0.0f, 1.0f });
        // 更新 model 到 cpu
        glUniformMatrix4fv(
            modelLocation, 1, GL_FALSE,
            glm::value_ptr(model));

        // 绑定唯一的材质到 slot 0
        glBindTexture(GL_TEXTURE_2D, renderable.material);
        // 绑定 vao 后渲染
        glBindVertexArray(renderable.VAO);
        glDrawArrays(GL_TRIANGLES, 0, renderable.vertexCount);
    }
    glfwSwapBuffers(window);
}