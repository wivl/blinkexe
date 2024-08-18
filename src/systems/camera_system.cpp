#include "camera_system.hpp"

CameraSystem::CameraSystem(unsigned int shader, GLFWwindow* window) {
	this->shader = shader;
	this->window = window;

	glUseProgram(shader);
	view_uniform_location = glGetUniformLocation(shader, "view");
}


void CameraSystem::update(std::unordered_map<unsigned int, TransformComponent>& transform_components, unsigned int camera_id, CameraComponent& camera_component, float delta_time) {
	auto& transform = transform_components.at(camera_id);

	// 获得鼠标输入，更新欧拉角
	double x_pos = 0.0f, y_pos = 0.0f;
	double screen_center_x = static_cast<double>(BLINK_WINDOW_WIDTH)/2.0f;
	double screen_center_y = static_cast<double>(BLINK_WINDOW_HEIGHT)/2.0f;
	glfwGetCursorPos(this->window, &x_pos, &y_pos);
	glfwSetCursorPos(this->window, screen_center_x, screen_center_y);
	glfwPollEvents();

	double xoffset = x_pos - screen_center_x, yoffset = y_pos - screen_center_y;
	float d_pitch = yoffset * camera_component.mouse_sensitivity;
	float d_yaw = xoffset * camera_component.mouse_sensitivity;

	camera_component.pitch += d_pitch;
	camera_component.yaw += d_yaw;

	if (camera_component.pitch > 89.0f) {
		camera_component.pitch = 89.0f;
	}
	if (camera_component.pitch < -89.0f) {
		camera_component.pitch = -89.0f;
	}

	glm::vec3 temp_direction = glm::vec3(0.0f, 0.0f, 0.0f);
	temp_direction.x = cos(glm::radians(camera_component.pitch)) * cos(glm::radians(camera_component.yaw));
	temp_direction.y = sin(glm::radians(camera_component.pitch));
	temp_direction.z = cos(glm::radians(camera_component.pitch)) * sin(glm::radians(camera_component.yaw));	
	camera_component.direction = glm::normalize(-temp_direction);
	camera_component.update_status();

	
	
	// 获得键盘输入，更新 transform
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(this->window, true);
	}
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) {
		transform.position -= camera_component.move_speed * delta_time * camera_component.direction;
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) {
		transform.position += camera_component.move_speed * delta_time * camera_component.direction;
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) {
		transform.position -= camera_component.move_speed * delta_time * camera_component.right;
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) {
		transform.position += camera_component.move_speed * delta_time * camera_component.right;
	}
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		transform.position += camera_component.move_speed * delta_time * glm::vec3(0.0f, 1.0f, 0.0f);
	}
	if (glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		transform.position -= camera_component.move_speed * delta_time * glm::vec3(0.0f, 1.0f, 0.0f);
	}

}
