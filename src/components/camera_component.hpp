#pragma once
#include "../config.hpp"

class CameraComponent {
public:
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 forwards;
public:
    CameraComponent() = default;
    CameraComponent(glm::vec3 right, glm::vec3 up, glm::vec3 forwards) : forwards(forwards) {
        this->right = glm::normalize(glm::cross(forwards, glm::vec3(0.0f, 1.0f, 0.0f)));
        this->up = glm::cross(right, forwards);
    }
    ~CameraComponent() = default;
};