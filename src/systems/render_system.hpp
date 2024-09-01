#pragma once
#include "../config.hpp"
#include "../components/transform_component.hpp"
#include "../components/render_component.hpp"

class RenderSystem {
public:

    RenderSystem(unsigned int shader, GLFWwindow* window);

    void update(
        std::unordered_map<unsigned int,TransformComponent> &transform_components,
        std::unordered_map<unsigned int,RenderComponent> &render_components);

private:

    unsigned int shader;
    unsigned int model_location;
    unsigned int normal_location;
    GLFWwindow* window;
};