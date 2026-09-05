#pragma once

#include <vector>
#include <glm/glm.hpp>

struct MeshRef;
struct Material;

struct RenderData {
	Material* mat;
	std::vector<MeshRef*> meshes;
	std::vector<glm::mat4> models;
};