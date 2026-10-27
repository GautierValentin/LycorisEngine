#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace glm;

class Entity;

#include "Component.h"

struct TransformDesc;

enum Space
{
	LOCAL = 1,
	GLOBAL = 2
};

class Transform : public Component
{
public:
	Transform(TransformDesc desc);
	~Transform();

	void Update() override;

public:
	vec3 _position;
	quat _rotation;
	vec3 _scale;

	mat4 _localMatrix;
	mat4 _worldMatrix;

	bool _localDirty = true;
	bool _worldDirty = true;

	Transform* _parent;
	std::vector<Transform*> _children;

public:
	void Translate(vec3 value, Space space = Space::LOCAL);
	void SetPosition(vec3 value, Space space = Space::LOCAL);

	void Rotate(quat value, Space space = Space::LOCAL);
	void SetRotation(quat value, Space space = Space::LOCAL);

	void Scale(vec3 value);
	void SetScale(vec3 value);

public:
	vec3 GetLocalPosition();
	vec3 GetGlobalPosition();

	quat GetLocalRotation();
	quat GetGlobalRotation();

public:
	void SetDirty();

public:
	void PushChild(Transform* child);

public:
	mat4 ComputeLocalMatrix();
	mat4 ComputeWorldMatrix();
};

struct TransformDesc {
	using ComponentType = Transform;
	Entity* entity;

	vec3 position;
	quat rotation;
	vec3 scale;

	Transform* parent = nullptr;

	TransformDesc() {
		position = vec3(0, 0, 0);
		rotation = quat(1, 0, 0, 0);
		scale = vec3(1, 1, 1);
	}
};