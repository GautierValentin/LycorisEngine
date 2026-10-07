#include "Scene.h"
#include "components/Collider.h"

Collider::Collider(ColliderDesc desc) : Component(desc.entity), _bodyType(desc.bodyType)
{
	Transform* transform = desc.entity->GetTransform();
	physx::PxVec3 position(transform->_position.x, transform->_position.y, transform->_position.z);
	physx::PxTransform pxTransform(position);

	_physicsActor = desc.scene->GetPhysicWorld().CreateActor(pxTransform, desc.geometry, desc.physicsMaterial, desc.bodyType);
}

Collider::~Collider()
{
}

void Collider::Update()
{
	if (_bodyType == BodyType::STATIC_BODY)
		return;

	physx::PxTransform fetchedTransform = _physicsActor->getGlobalPose();
	vec3 fetchedPos(fetchedTransform.p.x, fetchedTransform.p.y, fetchedTransform.p.z);

	_entity->GetTransform()->SetPosition(fetchedPos, Space::GLOBAL);
}
