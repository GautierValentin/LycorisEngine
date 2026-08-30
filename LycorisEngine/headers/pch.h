#pragma once

#include <vector>

struct MeshRef;
struct Material;

struct RenderData {
	Material* mat;
	std::vector<MeshRef*> meshes;
};