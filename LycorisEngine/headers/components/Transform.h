#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using namespace glm;

#include "Component.h"

struct TransformDesc;

class Transform : public Component
{
public:
	Transform(TransformDesc& desc);
	~Transform();

	void Update() override;

private:
	vec3 _position;
	vec3 _rotation;
	vec3 _scale;

public:
	void Translate(vec3 value);
	void Rotate(vec4 value);
	void Scale(vec3 value);
};

struct TransformDesc {
	using ComponentType = Transform;

	vec3 position;
	vec4 rotation;
	vec3 scale;
};