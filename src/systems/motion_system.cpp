#include "motion_system.hpp"

void MotionSystem::update(
    std::unordered_map<unsigned int,TransformComponent> &transform_components,
    std::unordered_map<unsigned int,PhysicsComponent> &physics_components,
    float dt) {

    for (auto& [entity, velocity] : physics_components) {
        transform_components[entity].position += velocity.velocity * dt;
        transform_components[entity].eulers += velocity.euler_velocity * dt;
        if (transform_components[entity].eulers.z > 360) {
            transform_components[entity].eulers.z -= 360;
        }
    }
}