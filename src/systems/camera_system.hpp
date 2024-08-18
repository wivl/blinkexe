#pragma once

#include "../components/transform_component.hpp"
#include "../components/camera_component.hpp"
#include "../config.hpp"


class CameraSystem {
private:
	unsigned int view_uniform_location;
	unsigned int shader;
	GLFWwindow* window;
public:
	CameraSystem() = delete;
	CameraSystem(unsigned int shader, GLFWwindow* window);
	~CameraSystem() = default;

	void update(
		std::unordered_map<unsigned int, TransformComponent>& transform_components,
		unsigned int camera_id,
		CameraComponent& camera_component,
		float delta_time
	);
};
