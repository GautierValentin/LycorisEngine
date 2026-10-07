#pragma once

#include<vector>

#include "pch.h"
#include "utils/LinkPtr.h"
#include "Entity.h"
#include "components/MeshRenderer.h"
#include "components/Transform.h"
#include "PhysicWorld.h"

class Scene {
public:
	Scene();
	~Scene();

private:
	PhysicWorld* _physicWorld;

private:
	std::vector<Entity> _entities;
	std::vector<Entity*> _needUpdateEntities; // Entities that need an update

	Entity* _camera;
	Entity* _light;

	LinkPtr<Entity>* _meshRenderers_ll;

	std::vector<RenderData> _renderData;

public:
	PhysicWorld& GetPhysicWorld() { return *_physicWorld; };

public:
	std::vector<RenderData> Update(float deltaTime);

	void UpdateEntitesComponentsReferences();

	Entity* Add(TransformDesc desc);

	Entity* SetCamera(Entity* entity);
	glm::mat4 GetCamView();

	Entity* SetLight(Entity* entity);
	std::pair<glm::vec3, glm::vec3> GetLightData();

private:
	void PackRenderData();
};