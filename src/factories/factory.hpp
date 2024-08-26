#pragma once
#include "../config.hpp"
#include "../components/camera_component.hpp"
#include "../components/physics_component.hpp"
#include "../components/render_component.hpp"
#include "../components/transform_component.hpp"
#include "../utils/model_loader.hpp"

class Factory {

public:
    Factory(
        std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents,
        std::unordered_map<unsigned int, RenderComponent>& renderComponents,
        std::unordered_map<unsigned int, TransformComponent>& transformComponents);

    ~Factory();

    unsigned int make_camera(glm::vec3 position, glm::vec3 eulers);

    void make_cube(glm::vec3 position, glm::vec3 eulers,
        glm::vec3 eulerVelocity);

    RenderComponent make_cube_mesh(glm::vec3 size);
    void make_girl(glm::vec3 position, glm::vec3 eulers);
private:

    unsigned int entities_made = 0;

    std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents;
    std::unordered_map<unsigned int, RenderComponent>& renderComponents;
    std::unordered_map<unsigned int, TransformComponent>& transformComponents;

    std::vector<unsigned int> VAOs;
    std::vector<unsigned int> VBOs;
    std::vector<unsigned int> textures;

    ModelLoader model_loader;


};