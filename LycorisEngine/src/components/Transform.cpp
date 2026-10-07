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
        _position += _rotation * value;
    }
    else {
        _position += value;
    }
    SetDirty();
}

void Transform::SetPosition(vec3 value, Space space)
{
    if (space == Space::LOCAL) {
        _position = _rotation * value;
    }
    else {
        _position = value;
    }

    SetDirty();
}

void Transform::Rotate(quat value, Space space = Space::LOCAL)
{
    if (space == Space::LOCAL) {
        _rotation *= value;
    }
    else {
        _rotation *= value;
    }
    
    SetDirty();
}

void Transform::SetRotation(quat value, Space space = Space::LOCAL)
{
    if (space == Space::LOCAL) {
        _rotation = value;
    }
    else {
        _rotation = value;
    }

    SetDirty();
}

void Transform::Scale(vec3 value)
{
	_scale *= value;
    SetDirty();
}

void Transform::SetScale(vec3 value)
{
    _scale = value;
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
    glm::mat4 rotationMatrix = glm::mat4_cast(_rotation);
    model = model * rotationMatrix;

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
