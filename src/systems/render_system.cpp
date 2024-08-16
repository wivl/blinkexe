#include "render_system.hpp"

RenderSystem::RenderSystem(unsigned int shader, GLFWwindow* window) : window{ window } {
	model_uniform_location = glGetUniformLocation(shader, "model");
}



RenderSystem::~RenderSystem() {
	window = nullptr;
}


void RenderSystem::update(
	std::unordered_map<unsigned int, TransformComponent>& transform_components,
	std::unordered_map<unsigned int, RenderComponent>& render_components
) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto entity : render_components) {
		auto& transform = transform_components[entity.first];
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transform.position);
						// matrix,    angle,    axis
		model = glm::rotate(model, glm::radians(transform.eulers.z), { 0.0f, 0.0f, 1.0f });
		glUniformMatrix4fv(model_uniform_location, 1, GL_FALSE, glm::value_ptr(model));
		glBindTexture(GL_TEXTURE_2D, entity.second.material);
		glBindVertexArray(entity.second.mesh);
		// TODO: 36
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glfwSwapBuffers(window);

}
