#include <glm/glm.hpp>

#include "Entity.h"
#include "Components/MeshRenderer.h"

MeshRenderer::MeshRenderer( MeshRendererDesc desc) : Component(desc.entity), _mesh(*(desc.meshRef)), _mat(*(desc.material))
{
}

MeshRenderer::MeshRenderer(MeshRenderer& other) : Component(other.GetEntity())
{
	_mesh = other._mesh;
	_mat = other._mat;
}

MeshRenderer::MeshRenderer(MeshRenderer&& other) : Component(other.GetEntity())
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
