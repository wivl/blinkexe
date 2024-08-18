#pragma once
#include "../config.hpp"

class CameraComponent {
public:
	glm::vec3 direction; // ָ�����Ŀ�귽����෴����
	glm::vec3 right;     // ��������ʾ������ռ�� x ��������
	glm::vec3 up;		 // ��ֱ����������������� direction �� up ����õ�
	float move_speed = 1.0f;  // ������ƶ��ٶ�
	float mouse_sensitivity = 0.1f;
	float pitch = 0.0f, yaw = 0.0f, roll = 0.0f;

public:
	CameraComponent() = default;
	CameraComponent(glm::vec3 position, glm::vec3 target_position) {
		this->direction = glm::normalize(position - target_position);
		this->right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), this->direction));
		this->up = glm::cross(this->direction, this->right);
	}

	~CameraComponent() = default;

	void update_status() {
		this->right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), this->direction));
		this->up = glm::cross(this->direction, this->right);
	}
};