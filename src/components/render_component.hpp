#pragma once
#include "../config.hpp"

class RenderComponent {
public:
    unsigned int albedo;
    unsigned int normal;
    unsigned int metallic;
    unsigned int roughness;
    unsigned int ao;
    unsigned int VAO;
    unsigned int vertexCount;
    RenderComponent() = default;
    RenderComponent(unsigned int material, unsigned int VAO, unsigned int vertexCount) : albedo(material), VAO(VAO), vertexCount(vertexCount) {}
    ~RenderComponent() = default;

};