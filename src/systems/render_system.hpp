#pragma once

#include "../config.hpp"
#include "../components/transform_component.hpp"
#include "../components/render_component.hpp"

class RenderSystem {
private:
	unsigned int model_uniform_location;
	unsigned int shader;
	GLFWwindow* window;
public:
	RenderSystem() = delete;
	RenderSystem(unsigned int shader, GLFWwindow* window);
	~RenderSystem() = default;

	void update(
		std::unordered_map<unsigned int, TransformComponent>& transform_components,
		std::unordered_map<unsigned int, RenderComponent>& render_components
	);
};