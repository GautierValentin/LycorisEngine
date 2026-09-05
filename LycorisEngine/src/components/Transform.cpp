#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "ECS/Entity.h"
#include "components/Transform.h"

Transform::Transform(TransformDesc desc) : Component(desc.entity), _position(desc.position), _rotation(desc.rotation), _scale(desc.scale), _parent(desc.parent)
{
    if(desc.parent != nullptr) {
        desc.parent->PushChild(this);
    }
}

Transform::~Transform()
{
}

void Transform::Update()
{
}

void Transform::Translate(vec3 value, Space space)
{
    if(space == Space::LOCAL){
        glm::mat4 rotationMatrix = glm::yawPitchRoll(
            _rotation.y,
            _rotation.x,
            _rotation.z
        );

        _position += glm::vec3(rotationMatrix * glm::vec4(value, 0.0f));
    }
    else {
        _position += value;
    }
    SetDirty();
}

void Transform::AddRotation(vec3 value)
{
    _rotation += glm::vec3(value.x, value.y, value.z);
    SetDirty();
}

void Transform::SetRotation(vec3 value)
{
    _rotation = glm::vec3(value.x, value.y, value.z);
    SetDirty();
}

void Transform::Scale(vec3 value)
{
	_scale *= value;
    SetDirty();
}

void Transform::SetDirty()
{
    _worldDirty = true;
    _localDirty = true;

    // Propagate to children
    for (Transform* child : _children) {
        child->SetDirty();
    }
}

void Transform::PushChild(Transform* child)
{
    _children.push_back(child);
}

mat4 Transform::ComputeLocalMatrix()
{
    if (false == _localDirty)
        return _localMatrix;

    glm::mat4 model = glm::mat4(1.0f);

    // Apply transformations in order: scale, rotate, translate
    model = glm::translate(model, _position);

    // Apply rotations around each axis
    model = glm::rotate(model, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Apply scaling
    model = glm::scale(model, _scale);

    _localMatrix = model;
    _localDirty = false;

    return _localMatrix;
}

mat4 Transform::ComputeWorldMatrix()
{
    if (false == _worldDirty)
        return _worldMatrix;

    if (_parent == nullptr) {
        _worldMatrix = ComputeLocalMatrix();
    }
    else {
        _worldMatrix = _parent->ComputeWorldMatrix() * ComputeLocalMatrix();
    }
    
    _worldDirty = false;

    return _worldMatrix;
}
