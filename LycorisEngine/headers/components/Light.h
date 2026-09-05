#pragma once
#include "Component.h"

#include <glm/glm.hpp>

struct LightDesc;

class Light : public Component
{
public:
	Light(LightDesc desc);
	~Light();

	void Update() override;

private:
	glm::vec3 _direction;
	glm::vec3 _color;

public:
	glm::vec3 GetColor() { return _color; };
	glm::vec3 ComputeDirection();
};

struct LightDesc {
	using ComponentType = Light;
	Entity* entity;

	glm::vec3 direction = glm::vec3(0, -.5f, -0.5f);
	glm::vec3 color;
};