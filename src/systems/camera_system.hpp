#pragma once
#include "../config.hpp"
#include "../components/camera_component.hpp"
#include "../components/transform_component.hpp"

class CameraSystem {
private:
    unsigned int view_location;
    unsigned int camera_position_location;
    glm::vec3 global_up = {0.0f, 0.0f, 1.0f};
    GLFWwindow* window;
public:
    CameraSystem(unsigned int shader, GLFWwindow* window);

    // 更新摄像机的键盘和鼠标控制
    bool update(
        std::unordered_map<unsigned int,TransformComponent> &transform_components,
        unsigned int camera_id, CameraComponent& camera_component, float dt);
};