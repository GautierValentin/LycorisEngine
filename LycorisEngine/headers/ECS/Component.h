#pragma once

class Component
{
public:
	Component();
	Component(Component& other);
	Component(Component&& other);
	~Component();
};

