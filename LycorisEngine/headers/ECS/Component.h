#pragma once

class Component
{
public:
	Component();
	Component(Component& other);
	Component(Component&& other);
	~Component();

public:
	virtual void Update() = 0;
};

