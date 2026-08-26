#pragma once

#include <vector>

#include "Vertex.h"

struct Mesh {



	// temp
	Mesh() {
		vertices = {
			{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
			{{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
			{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}},
			{{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
			{{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
		};
		indices = {
			0, 1, 2, 2, 3, 0, 0, 1, 5, 5, 6, 7, 4, 5, 6
		};
	};

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
};