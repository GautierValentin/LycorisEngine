#include "components/Transform.h"

Transform::Transform(TransformDesc& desc) : _position(desc.position), _rotation(desc.rotation), _scale(desc.scale)
{
}

Transform::~Transform()
{
}

void Transform::Translate(vec3 value)
{
	_position += value;
}

void Transform::Rotate(vec4 value)
{
}

void Transform::Scale(vec3 value)
{
	_scale *= value;
}
