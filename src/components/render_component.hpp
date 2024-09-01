#pragma once
#include "../config.hpp"

class RenderComponent {
public:
    unsigned int albedo;
    unsigned int normal;
    unsigned int metallic;
    unsigned int roughness;
    unsigned int ao;
    unsigned int vao;
    unsigned int vertex_count;
    RenderComponent() = default;
    RenderComponent(unsigned int material, unsigned int vao, unsigned int vertex_count) : albedo(material), vao(vao), vertex_count(vertex_count) {}
    ~RenderComponent() = default;

};