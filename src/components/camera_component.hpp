#pragma once
#include <glm/glm.hpp>

class CameraComponent {
public:
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 forwards;
public:
	CameraComponent() = default;
	CameraComponent(glm::vec3 right, glm::vec3 up, glm::vec3 forwards) : right{ right }, up{ up }, forwards{ forwards } {};
	~CameraComponent() = default;
};