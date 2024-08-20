#pragma once
#include "../config.hpp"

class TransformComponent {
public:
    glm::vec3 position;
    glm::vec3 eulers;
public:
    TransformComponent() = default;
    TransformComponent(glm::vec3 position, glm::vec3 eulers) : position(position), eulers(eulers) {}
    ~TransformComponent() = default;
};