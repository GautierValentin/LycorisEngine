#pragma once

#include<vector>

#include "pch.h"
#include "utils/LinkPtr.h"
#include "Entity.h"
#include "components/MeshRenderer.h"

class Scene {
public:
	Scene();
	~Scene();

private:
	std::vector<Entity> _entities;
	std::vector<Entity*> _needUpdateEntities; // Entities that need an update

	LinkPtr<MeshRenderer>* _meshRenderers_ll;

	std::vector<RenderData> _renderData;

public:
	std::vector<RenderData> Update();

	void UpdateEntitesComponentsReferences();

	Entity* Add();

private:
	void PackRenderData();
};