#pragma once

class RenderComponent {
public:
	unsigned int material;
	unsigned int mesh;
public:
	RenderComponent() = default;
	RenderComponent(unsigned int material, unsigned int mesh) : material{ material }, mesh{ mesh } {};
	~RenderComponent() = default;
};