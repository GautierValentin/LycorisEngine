#pragma once

#include <memory>

#include "Renderer.h"
#include "Scene.h"
#include "ResourcesAllocator.h"

class Application
{
public:
	Application();
	~Application();

	int Init(uint32_t width, uint32_t height);
	int UnInit();

public:
	void Run();

public:
	GLFWwindow* _win;
	Renderer* _renderer;
	Scene* _scene;
	ResourcesAllocator* _allocator;

	std::unordered_map<std::string, MeshRef> _loadedMeshes;

	//temp
	Entity* _entity;
	Entity* _entity2;
	Entity* _cam;
};

