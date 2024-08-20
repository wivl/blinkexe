#pragma once
#include "../config.hpp"
#include "../components/transform_component.hpp"
#include "../components/render_component.hpp"

class RenderSystem {
public:

    RenderSystem(unsigned int shader, GLFWwindow* window);

    void update(
        std::unordered_map<unsigned int,TransformComponent> &transformComponents,
        std::unordered_map<unsigned int,RenderComponent> &renderComponents);

private:

    unsigned int modelLocation;
    GLFWwindow* window;
};