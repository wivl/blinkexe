#pragma once
#include "../config.hpp"


class PhysicsComponent {
public:
    glm::vec3 velocity;       // 速度
    glm::vec3 euler_velocity;  // 旋转速度

    PhysicsComponent() = default;
    PhysicsComponent(glm::vec3 velocity, glm::vec3 euler_velocity) : velocity(velocity), euler_velocity(euler_velocity) {}
    ~PhysicsComponent() = default;
};
