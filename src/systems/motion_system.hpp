#pragma once
#include "../config.hpp"
#include "../components/transform_component.hpp"
#include "../components/physics_component.hpp"

class MotionSystem {
public:

    // 根据 physics 组件的速度信息更新 transform 组件
    void update(
        std::unordered_map<unsigned int,TransformComponent> &transformComponents,
        std::unordered_map<unsigned int,PhysicsComponent> &physicsComponents,
        float dt);
};