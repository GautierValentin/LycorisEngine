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
	
}

// Copy transform into physicsWorld transform
void Collider::UploadPhysics() 
{
	vec3 pos = _entity->GetTransform()->GetGlobalPosition();
	physx::PxVec3 pxPos = physx::PxVec3(pos.x, pos.y, pos.z);

	quat rot = _entity->GetTransform()->GetGlobalRotation();
	physx::PxQuat pxRot = physx::PxQuat(rot.w, rot.x, rot.y, rot.z); //TODO: why the hell do I need to set w first here and last in download? there's smth wrong somewhere

	physx::PxTransform physicsTransform(pxPos, pxRot);

	_physicsActor->setGlobalPose(physicsTransform);
}

// Fetch PhysicsWorld and apply it to transform
void Collider::DownloadPhysics() 
{
	if (_bodyType == BodyType::STATIC_BODY)
		return;

	physx::PxTransform fetchedTransform = _physicsActor->getGlobalPose();

	vec3 fetchedPos(fetchedTransform.p.x, fetchedTransform.p.y, fetchedTransform.p.z);
	_entity->GetTransform()->SetPosition(fetchedPos, Space::GLOBAL);

	glm::quat fetchedRot(fetchedTransform.q.x, fetchedTransform.q.y, fetchedTransform.q.z, fetchedTransform.q.w);
	_entity->GetTransform()->SetRotation(fetchedRot, Space::GLOBAL);
}
