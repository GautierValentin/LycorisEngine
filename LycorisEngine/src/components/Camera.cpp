#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "ECS/Entity.h"
#include "components/Transform.h"
#include "components/Camera.h"

Camera::Camera(CameraDesc desc) : Component(desc.entity)
{
	
}

Camera::~Camera()
{
}

void Camera::Update()
{
}

glm::mat4 Camera::ComputeViewMatrix()
{
	Transform* tr;
	GetEntity()->TryFind(tr);

	glm::vec3 pos = tr->_position;
	glm::vec3 target = tr->_position + glm::vec3(1, 0, 0) * tr->_rotation;

	glm::mat4 rotationMatrix = glm::yawPitchRoll( tr->_rotation.y, tr->_rotation.x, tr->_rotation.z );

	glm::mat4 view = glm::inverse( glm::translate(glm::mat4(1.0f), tr->_position) * rotationMatrix );

	return view;
}
