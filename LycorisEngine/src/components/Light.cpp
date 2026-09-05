#include <glm/gtc/matrix_transform.hpp>

#include "components/Transform.h"
#include "ECS/Entity.h"
#include "components/Light.h"

Light::Light(LightDesc desc) : Component(desc.entity), _direction(desc.direction), _color(desc.color)
{
}

Light::~Light()
{
}

void Light::Update()
{
}

glm::vec3 Light::ComputeDirection()
{
    glm::mat4 rotateMatrix = _entity->GetTransform()->ComputeWorldMatrix();
    glm::vec4 dir = glm::vec4(_direction.x, _direction.y, _direction.z, 0);
    return dir * rotateMatrix;
}
