#pragma once

#include <glm/glm.hpp>

class TransformComponent {
public:
	glm::vec3 position;
	// TODO: ������ת�ײ㴦��Ϊ��Ԫ��
	glm::vec3 rotation;
	glm::vec3 scale;
public:
	TransformComponent() = delete;
	TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}
	~TransformComponent() = default;
};