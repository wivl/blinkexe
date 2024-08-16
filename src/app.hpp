#pragma once

#include "config.hpp"
#include "systems/camera_system.hpp"
#include "systems/render_system.hpp"

class App {
private:
#ifdef BLINK_DEBUG
	unsigned int frame = 0;
#endif
	unsigned int entity_count = 0;
	GLFWwindow* window;
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
	std::vector<unsigned int> textures;

	unsigned int shader;

	std::shared_ptr<CameraSystem> camera_system;
	std::shared_ptr<RenderSystem> render_system;

public:
	std::unordered_map<unsigned int, TransformComponent> transform_components;
	std::unordered_map<unsigned int, RenderComponent> render_components;


	std::shared_ptr<CameraComponent> camera_component;
	unsigned int camera_id;

private:
	void setup_glfw();


public:
	App();
	~App();
	void run();
	unsigned int make_entity();
	unsigned int make_cube_mesh(glm::vec3 size);
	unsigned int make_texture(std::string filename);
	void setup_opengl();
	void make_systems();

};
