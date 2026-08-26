#pragma once

#include<vector>

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

public:
	void Update();

	void UpdateEntitesComponentsReferences();

	Entity* Add();
};