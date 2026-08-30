#pragma once

#include <vector>
#include <unordered_map>
#include <iostream>

#include "Vertex.h"

enum MeshType
{
	STATIC
};

struct MeshDesc;

struct MeshData {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
};

struct MeshRef {
	// id in its buffer
	uint8_t id;
	MeshType type;
};

struct MeshDesc {
	char* path;
	char* name;
	MeshType type;
	std::unordered_map<std::string, MeshRef>& dest;
};