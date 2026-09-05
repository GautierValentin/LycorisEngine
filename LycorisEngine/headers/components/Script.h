#pragma once

class Entity;
struct ScriptDesc;

#include <GLFW/glfw3.h>
#include "Component.h"

class Script : public Component
{
public:
	Script(ScriptDesc desc);
	~Script();

	void Update() override {};

protected:
	GLFWwindow* _win;
};

struct ScriptDesc {
	using ComponentType = Script;
	Entity* entity;

	GLFWwindow* window;
};