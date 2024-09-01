#include "factory.hpp"
#include <stb_image.h>

Factory::Factory(
    std::unordered_map<unsigned int, PhysicsComponent>& physics_components,
    std::unordered_map<unsigned int, RenderComponent>& render_components,
    std::unordered_map<unsigned int, TransformComponent>& transform_components):
physics_components(physics_components),
render_components(render_components),
transform_components(transform_components) {
}

Factory::~Factory() {
    glDeleteBuffers(vbos.size(), vbos.data());
    glDeleteVertexArrays(vaos.size(), vaos.data());
    glDeleteTextures(textures.size(), textures.data());
}

unsigned int Factory::make_camera(glm::vec3 position, glm::vec3 eulers) {

    TransformComponent transform;
    transform.position = position;
    transform.eulers = eulers;

    transform_components[entities_made] = transform;

    return entities_made++;
}


void Factory::make_cube(glm::vec3 position, glm::vec3 eulers,
    glm::vec3 euler_velocity) {

	TransformComponent transform{};
	transform.position = position;
	transform.eulers = eulers;
	transform_components[entities_made] = transform;

	PhysicsComponent physics{};
	physics.velocity = {0.0f, 0.0f, 0.0f};
	physics.euler_velocity = euler_velocity;
	physics_components[entities_made] = physics;

	RenderComponent render = make_cube_mesh({0.25f, 0.25f, 0.25f});
	model_loader.set_texture(render, "../assets/brick.png");
	render_components[entities_made++] = render;
}

RenderComponent Factory::make_cube_mesh(glm::vec3 size) {

    float l = size.x;
    float w = size.y;
    float h = size.z;

    std::vector<float> vertices = {
         l,  w, -h, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
         l, -w, -h, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
        -l, -w, -h, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
        -l, -w, -h, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
        -l,  w, -h, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
         l,  w, -h, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,

        -l, -w,  h, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
         l, -w,  h, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
         l,  w,  h, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
         l,  w,  h, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -l,  w,  h, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -l, -w,  h, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

        -l,  w,  h, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -l,  w, -h, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -l, -w, -h, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -l, -w, -h, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -l, -w,  h, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -l,  w,  h, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,

         l, -w, -h, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         l,  w, -h, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         l,  w,  h, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         l,  w,  h, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         l, -w,  h, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         l, -w, -h, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,

        -l, -w, -h, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
         l, -w, -h, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
         l, -w,  h, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
         l, -w,  h, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
        -l, -w,  h, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
        -l, -w, -h, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,

         l,  w,  h, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
         l,  w, -h, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -l,  w, -h, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -l,  w, -h, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -l,  w,  h, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
         l,  w,  h, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    vaos.push_back(vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    vbos.push_back(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
        vertices.data(), GL_STATIC_DRAW);
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (void*)0);
    glEnableVertexAttribArray(0);
    //texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void*)12);
    glEnableVertexAttribArray(1);
    //normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (void*)20);
    glEnableVertexAttribArray(2);

    RenderComponent record;
    record.vao = vao;
    record.vertex_count = 36;
    return record;
}

void Factory::make_girl(glm::vec3 position, glm::vec3 eulers) {
    TransformComponent transform{};
    transform.position = position;
    transform.eulers = eulers;
    transform_components[entities_made] = transform;


    glm::mat4 pre_transform = glm::mat4(1.0f);
    pre_transform = glm::rotate(pre_transform,
        glm::radians(90.0f), { 1.0f, 0.0f, 0.0f });
    pre_transform = glm::rotate(pre_transform,
        glm::radians(90.0f), { 0.0f, 1.0f, 0.0f });
    RenderComponent render = model_loader.load("../assets/girl.obj", pre_transform);
    model_loader.set_texture(render, "../assets/stargirl.png");
    render_components[entities_made++] = render;

}


void Factory::make_sphere(glm::vec3 position, glm::vec3 eulers, glm::vec3 euler_velocity) {
    TransformComponent transform{};
    transform.position = position;
    transform.eulers = eulers;
    transform_components[entities_made] = transform;

    PhysicsComponent physics{};
    physics.velocity = {0.0f, 0.0f, 0.0f};
    physics.euler_velocity = euler_velocity;
    physics_components[entities_made] = physics;

    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), { 1.0f, 0.0f, 0.0f });
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), { 0.0f, 1.0f, 0.0f });

    RenderComponent render = model_loader.load("../assets/sphere.obj", preTransform);

    render.albedo = model_loader.make_texture("../assets/rustediron1-alt2-Unreal-Engine/basecolor.png");
    render.normal = model_loader.make_texture("../assets/rustediron1-alt2-Unreal-Engine/normal.png");
    render.metallic = model_loader.make_texture("../assets/rustediron1-alt2-Unreal-Engine/metallic.png");
    render.roughness = model_loader.make_texture("../assets/rustediron1-alt2-Unreal-Engine/roughness.png");
    render.ao = model_loader.make_texture("../assets/rustediron1-alt2-Unreal-Engine/ao.png");

    render_components[entities_made++] = render;
}



