#pragma once
#include "../config.hpp"
#include "../components/camera_component.hpp"
#include "../components/physics_component.hpp"
#include "../components/render_component.hpp"
#include "../components/transform_component.hpp"
#include "../utils/model_loader.hpp"

class Factory {

public:
    // 获得组件 map 的引用
    Factory(
        std::unordered_map<unsigned int, PhysicsComponent>& physics_components,
        std::unordered_map<unsigned int, RenderComponent>& render_components,
        std::unordered_map<unsigned int, TransformComponent>& transform_components);

    ~Factory();

    // 创建摄像机
    unsigned int make_camera(glm::vec3 position, glm::vec3 eulers);

    void make_cube(glm::vec3 position, glm::vec3 eulers, glm::vec3 euler_velocity);

    void make_sphere(glm::vec3 position, glm::vec3 eulers, glm::vec3 euler_velocity);

    void make_girl(glm::vec3 position, glm::vec3 eulers);
private:

    unsigned int entities_made = 0;

    std::unordered_map<unsigned int, PhysicsComponent>& physics_components;
    std::unordered_map<unsigned int, RenderComponent>& render_components;
    std::unordered_map<unsigned int, TransformComponent>& transform_components;

    std::vector<unsigned int> vaos;
    std::vector<unsigned int> vbos;
    std::vector<unsigned int> textures;

    ModelLoader model_loader;

    RenderComponent make_cube_mesh(glm::vec3 size);

};