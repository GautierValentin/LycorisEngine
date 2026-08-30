#include <glm/glm.hpp>

#include "Components/MeshRenderer.h"

MeshRenderer::MeshRenderer(MeshRendererDesc desc) : _mesh(*(desc.meshRef)), _mat(*(desc.material))
{
}

MeshRenderer::MeshRenderer(MeshRenderer& other)
{
	_mesh = other._mesh;
	_mat = other._mat;
}

MeshRenderer::MeshRenderer(MeshRenderer&& other)
{
	_mesh = std::move(other._mesh);
	_mat = std::move(other._mat);
}

MeshRenderer::~MeshRenderer()
{
	_mat.Free();
}

void MeshRenderer::Update()
{
}
