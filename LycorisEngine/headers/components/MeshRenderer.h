#pragma once

#include "Component.h"
#include "Mesh.h"
#include "Material.h"

struct MeshRendererDesc;

class MeshRenderer : public Component
{
public:
	MeshRenderer(MeshRendererDesc desc);
	~MeshRenderer();

private:
	Mesh* _mesh;
	Material* _mat;
};

struct MeshRendererDesc{
	using ComponentType = MeshRenderer;


};