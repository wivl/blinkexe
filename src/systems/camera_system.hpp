#pragma once
#include "../config.hpp"
#include "../components/camera_component.hpp"
#include "../components/transform_component.hpp"

class CameraSystem {
private:
    unsigned int viewLocation;
    unsigned int cameraPositionLocation;
    glm::vec3 global_up = {0.0f, 0.0f, 1.0f};
    GLFWwindow* window;
public:
    CameraSystem(unsigned int shader, GLFWwindow* window);

    // 更新摄像机的键盘和鼠标控制
    bool update(
        std::unordered_map<unsigned int,TransformComponent> &transformComponents,
        unsigned int cameraID, CameraComponent& cameraComponent, float dt);
};