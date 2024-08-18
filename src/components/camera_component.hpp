#pragma once
#include "../config.hpp"

class CameraComponent {
public:
	glm::vec3 direction; // 指向从它目标方向的相反方向
	glm::vec3 right;     // 右向量表示摄像机空间的 x 轴正方向
	glm::vec3 up;		 // 垂直摄像机的上向量，由 direction 和 up 计算得到
	float move_speed = 1.0f;  // 摄像机移动速度
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