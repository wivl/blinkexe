#include "render_system.hpp"

RenderSystem::RenderSystem(unsigned int shader, GLFWwindow* window) : shader(shader), window(window) {
	model_uniform_location = glGetUniformLocation(shader, "model");
}

glm::mat4 _get_model_matrix(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) {
	glm::mat4 model = glm::mat4(1.0f);

	// 应用缩放
	model = glm::scale(model, scale);

	// 应用旋转 (注意：旋转顺序是先 Z 后 Y 再 X)
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // 绕 Z 轴旋转
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // 绕 Y 轴旋转
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // 绕 X 轴旋转

	// 应用平移
	model = glm::translate(model, position);

	return model;
}

void RenderSystem::update(std::unordered_map<unsigned int, TransformComponent>& transform_components, std::unordered_map<unsigned int, RenderComponent>& render_components) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto entity : render_components) {
		auto& transform = transform_components.at(entity.first);
		// 不同的模型有不同的 model matrix
		glm::mat4 model = _get_model_matrix(transform.position, transform.position, transform.scale);
		glUniformMatrix4fv(model_uniform_location, 1, GL_FALSE, glm::value_ptr(model));

		glBindTexture(GL_TEXTURE_2D, entity.second.material);
		glBindVertexArray(entity.second.mesh);
		// TODO: 

	}
}