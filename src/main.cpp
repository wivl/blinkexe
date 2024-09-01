#include "config.hpp"
#include "app.hpp"

#include "components/camera_component.hpp"
#include "components/physics_component.hpp"
#include "components/render_component.hpp"
#include "components/transform_component.hpp"

#include "factories/factory.hpp"
int main() {

    App* app = new App();
    Factory* factory = new Factory(
        app->physics_components,
        app->render_components, app->transform_components);

    factory->make_sphere(
        {3.0f, 0.0f, 0.25f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 10.0f});


    unsigned int camera_entity = factory->make_camera(
        {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f,0.0f});

    CameraComponent* camera = new CameraComponent();
    app->camera_component = camera;
    app->cameraID = camera_entity;

    app->set_up_opengl();
    app->make_systems();

    app->run();

    delete factory;
    delete app;
    return 0;
}
