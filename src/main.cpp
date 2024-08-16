#include "config.hpp"
#include "app.hpp"

int main() {
	auto app = std::make_shared<App>();
	unsigned int cube_entity{ app->make_entity() };
	TransformComponent transform;
	transform.position = { 3.0f, 0.0f, 0.25f };
	transform.eulers = { 0.0f, 0.0f, 0.0f };
	app->transform_components[cube_entity] = transform;

	RenderComponent render;
	render.mesh = app->make_cube_mesh({0.25f, 0.25f, 0.25f });
	render.material = app->make_texture("../assets/concrete.jpg");
	app->render_components[cube_entity] = render;

	unsigned int camera_entity{ app->make_entity() };
	transform.position = { 0.0f, 0.0f, 1.0f };
	transform.eulers = { 0.0f, 0.0f, 0.0f };
	app->transform_components[camera_entity] = transform;

	app->camera_component = std::make_shared<CameraComponent>();
	app->camera_id = camera_entity;

	app->setup_opengl();
	app->make_systems();
	app->run();

}	


