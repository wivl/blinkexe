#pragma once
#include "config.hpp"

#include "components/camera_component.hpp"
#include "components/physics_component.hpp"
#include "components/render_component.hpp"
#include "components/transform_component.hpp"

#include "systems/camera_system.hpp"
#include "systems/motion_system.hpp"
#include "systems/render_system.hpp"

#include "utils/shader.hpp"

class App {
public:
    App();
    ~App();
    void run();
    void set_up_opengl();
    void make_systems();

    //Components
    std::unordered_map<unsigned int, TransformComponent> transform_components;
    std::unordered_map<unsigned int, PhysicsComponent> physics_components;
    CameraComponent* camera_component;
    unsigned int cameraID;
    std::unordered_map<unsigned int, RenderComponent> render_components;

private:
    void set_up_glfw();

    GLFWwindow* window;

    unsigned int shader;

    //Systems
    MotionSystem* motion_system;
    CameraSystem* camera_system;
    RenderSystem* render_system;
};