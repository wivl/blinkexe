#pragma once

#include "../config.hpp"
#include "../components/render_component.hpp"
#include <tiny_obj_loader.h>

class ModelLoader {
public:
    ModelLoader();
    ~ModelLoader() = default;
    RenderComponent load(std::string file_path, glm::mat4 preModelMatrix = glm::mat4(1.0f));
    void set_texture(RenderComponent& render_component, std::string texture_path);
private:
    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig config;

    unsigned int make_texture(const char* filename);

};
