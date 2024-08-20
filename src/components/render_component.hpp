#pragma once
#include "../config.hpp"

class RenderComponent {
public:
    unsigned int material, VAO, vertexCount;
    RenderComponent() = default;
    RenderComponent(unsigned int material, unsigned int VAO, unsigned int vertexCount) : material(material), VAO(VAO), vertexCount(vertexCount) {}
    ~RenderComponent() = default;

};