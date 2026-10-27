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

	// Formula: view = inverse( T(position) * R(rotation) )

	glm::mat4 view = glm::mat4_cast(glm::conjugate(tr->_rotation));
	view = glm::translate(view, -tr->_position);

	return view;
}
