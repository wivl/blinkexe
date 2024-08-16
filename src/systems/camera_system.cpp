#include "camera_system.hpp"

CameraSystem::CameraSystem(unsigned int shader, GLFWwindow* window) : window{ window } {
	glUseProgram(shader);
	view_uniform_location = glGetUniformLocation(shader, "view");
}

CameraSystem::~CameraSystem() {
	window = nullptr;
	glUseProgram(0);
}

// TODO: ÖØÐ´ camera Âß¼­
bool CameraSystem::update(
	std::unordered_map<unsigned int, TransformComponent>& transform_components,
	unsigned int camera_id,
	CameraComponent& camera_component,
	float delta_time
) {
	glm::vec3& pos = transform_components[camera_id].position;
	glm::vec3& eulers = transform_components[camera_id].eulers;
	float theta = glm::radians(eulers.z);
	float phi = glm::radians(eulers.y);

	glm::vec3& right = camera_component.right;
	glm::vec3& up = camera_component.up;
	glm::vec3& forwards = camera_component.forwards;

	forwards = {
		glm::cos(theta) * glm::cos(phi),
		glm::sin(theta) * glm::cos(phi),
		glm::sin(phi)
	};
	right = glm::normalize(glm::cross(forwards, global_up));
	up = glm::normalize(glm::cross(right, forwards));

	glm::mat4 view = glm::lookAt(pos, pos + forwards, up);
	glUniformMatrix4fv(view_uniform_location, 1, GL_FALSE, glm::value_ptr(view));

	// keys
	glm::vec3 dpos = { 0.0f, 0.0f, 0.0f };
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		dpos.x += 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		dpos.y -= 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		dpos.x -= 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		dpos.y += 1.0f;
	}
	if (glm::length(dpos) > 0.1f) {
		dpos = glm::normalize(dpos);
		pos += 0.1f * dpos.x * forwards;
		pos += 0.1f * dpos.y * right;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		return true;
	}

	// Mouse
	glm::vec3 deulers = { 0.0f, 0.0f, 0.0f };
	double mouse_x, mouse_y;
	glfwGetCursorPos(window, &mouse_x, &mouse_y);
	glfwSetCursorPos(window, BLINK_WINDOW_WIDTH / 2, BLINK_WINDOW_HEIGHT / 2);
	glfwPollEvents();

	deulers.z = -0.01f * static_cast<float>(mouse_x - BLINK_WINDOW_WIDTH / 2);
	deulers.y = -0.01f * static_cast<float>(mouse_y - BLINK_WINDOW_HEIGHT / 2);

	eulers.y = fminf(89.0f, fmaxf(-89.0f, eulers.y + deulers.y));

	eulers.z += deulers.z;

	if (eulers.z > 360) {
		eulers.z -= 360;
	}
	else if (eulers.z < 0) {
		eulers.z += 360;
	}

	return false;
}
