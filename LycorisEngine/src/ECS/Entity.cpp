#include "Entity.h"

Entity::Entity(std::function<void(Entity*)> needUpdateCallback) : _needUpdateCallback(needUpdateCallback)
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
}
