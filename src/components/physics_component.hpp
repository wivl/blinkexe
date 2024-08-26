#pragma once
#include "../config.hpp"


class PhysicsComponent {
public:
    glm::vec3 velocity;       // 速度
    glm::vec3 eulerVelocity;  // 旋转速度

    PhysicsComponent() = default;
    PhysicsComponent(glm::vec3 velocity, glm::vec3 eulerVelocity) : velocity(velocity), eulerVelocity(eulerVelocity) {}
    ~PhysicsComponent() = default;
};
