#pragma once

#include "Component.h"
#include "Mesh.h"
#include "Material.h"

struct MeshRendererDesc;

class MeshRenderer : public Component
{
public:
	MeshRenderer(MeshRendererDesc desc);
	MeshRenderer(MeshRenderer& other);
	MeshRenderer(MeshRenderer&& other);
	~MeshRenderer();

	void Update() override;

public:
	MeshRef _mesh;
	Material _mat;
};

struct MeshRendererDesc{
	using ComponentType = MeshRenderer;
	Entity* entity;

	MeshRef* meshRef;
	Material* material;
};