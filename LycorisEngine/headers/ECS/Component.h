#pragma once

class Entity;

class Component
{
public:
	Component(Entity* entity);
	Component(Component& other);
	Component(Component&& other);
	~Component();

public:
	virtual void Update() = 0;

	Entity* GetEntity();

protected:
	Entity* _entity;

};

