#include <glm/glm.hpp>
#include "Scene.h"

Scene::Scene()
{
    _meshRenderers_ll = new LinkPtr<MeshRenderer>(nullptr, nullptr, nullptr);
    _entities.reserve(4);
}

Scene::~Scene()
{
}

void Scene::Update()
{
    UpdateEntitesComponentsReferences();
}

void Scene::UpdateEntitesComponentsReferences()
{
    for (Entity* entity : _needUpdateEntities) {
        entity->_needUpdate = false;

        MeshRenderer* mr = nullptr;
        if (entity->TryFind<MeshRenderer>(mr)) {
            if (false == _meshRenderers_ll->Contains(mr)) {
                _meshRenderers_ll->Add(mr);
            }
        }
    }
    _needUpdateEntities.empty();
}

Entity* Scene::Add()
{
    std::function<void(Entity*)> func = [this](Entity* self) {this->_needUpdateEntities.push_back(self); };

    Entity& entity = _entities.emplace_back(func);
    

    return &entity;
}
