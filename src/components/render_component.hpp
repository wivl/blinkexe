#pragma once

// ��Ҫ��Ⱦ�����
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