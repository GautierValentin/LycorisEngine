#include <iostream>

#include "Entity.h"
#include "components/Transform.h"

Entity::Entity(std::function<void(Entity*)> needUpdateCallback) : _needUpdateCallback(needUpdateCallback), _transform(nullptr)
{
	_needUpdate = true;
	_needUpdateCallback(this);
}

Entity::Entity(Entity&& other)
{
	_needUpdate = true;
	_components = std::move(other._components);
	_needUpdateCallback = std::move(other._needUpdateCallback);

	other._needUpdate = true;
}

Entity::~Entity()
{
	for (Component* comp : _components)
		delete comp;
}

void Entity::Update()
{
	for (Component* comp : _components)
		comp->Update();
}

void Entity::AssignTransform()
{
	if (_transform != nullptr)
		throw std::runtime_error("transform has already been assigned");

	TryFind(_transform);
}
