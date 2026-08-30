#pragma once

#include <iostream>
#include <unordered_map>

class Renderer;

#include "Vertex.h"
#include "Mesh.h"

//class Renderer;

class ResourcesAllocator
{
public:
	ResourcesAllocator(Renderer* renderer);
	~ResourcesAllocator();

public:
	MeshRef& LoadMesh(const std::string path, const std::string name, MeshType type, std::unordered_map<std::string, MeshRef>& dest);

private:
	Renderer* _renderer;
};

