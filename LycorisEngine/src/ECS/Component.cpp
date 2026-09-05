#include"Component.h"

Component::Component(Entity* entity) : _entity(entity)
{
}

Component::Component(Component& other)
{
}

Component::Component(Component&& other)
{
}

Component::~Component()
{
}

Entity* Component::GetEntity()
{
    return _entity;
}
