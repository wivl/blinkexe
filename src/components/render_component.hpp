#pragma once

// 需要渲染的组件
class RenderComponent {
public:
	unsigned int material;
	unsigned int mesh;

public:
	RenderComponent() = delete;
	RenderComponent(unsigned int material, unsigned int mesh) {
		this->material = material;
		this->mesh = mesh;
	}
	~RenderComponent() = default;
};