#pragma once

#include <glm/glm.hpp>

class TransformComponent {
public:
	glm::vec3 position; // Œª÷√
	glm::vec3 eulers;   // ≈∑¿≠Ω«
public:
	TransformComponent() = default;
	TransformComponent(glm::vec3 position, glm::vec3 eulers) : position{ position }, eulers{ eulers } {};

	~TransformComponent() = default;
};