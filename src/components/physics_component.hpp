#pragma once
#include "../config.hpp"

class PhysicsComponent {
public:
    glm::vec3 velocity;
    glm::vec3 eulerVelocity;

public:
    PhysicsComponent() = default;

    PhysicsComponent(glm::vec3 velocity, glm::vec3 eulerVelocity) : velocity(velocity), eulerVelocity(eulerVelocity) {}

    ~PhysicsComponent() = default;
};
