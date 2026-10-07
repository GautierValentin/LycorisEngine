#pragma once

#include <PxPhysics.h>

class Scene;
class Entity;

#include "Component.h"

struct ColliderDesc;

class Collider : public Component
{
public:
	Collider(ColliderDesc desc);
	~Collider();

	void Update() override;

private:
	physx::PxRigidActor* _physicsActor;
	BodyType _bodyType;
};


struct ColliderDesc{
	using ComponentType = Collider;
	Entity* entity;

	Scene* scene;
	physx::PxGeometry* geometry;
	const char* physicsMaterial;
	BodyType bodyType;

	ColliderDesc() {};
};
