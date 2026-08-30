#include <map>
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

std::vector<RenderData> Scene::Update()
{
    UpdateEntitesComponentsReferences();
    PackRenderData();

    return _renderData;
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
    _needUpdateEntities.clear();
}

Entity* Scene::Add()
{
    std::function<void(Entity*)> func = [this](Entity* self) {this->_needUpdateEntities.push_back(self); };

    Entity& entity = _entities.emplace_back(func);
    

    return &entity;
}

// Distribute specific components ref into dedicated virtual arrays
void Scene::PackRenderData()
{
    if (_meshRenderers_ll == nullptr)
        return;

    _renderData.clear();

    std::map<Material*, std::vector<MeshRef*>> bindings;

    LinkPtr<MeshRenderer>* lPtr = _meshRenderers_ll;
    while (lPtr != nullptr && lPtr->GetRef() != nullptr) {
        Material& mat = lPtr->GetRef()->_mat;
        MeshRef& mesh = lPtr->GetRef()->_mesh;

        //if (bindings.contains(mat)) {
            bindings[&mat].push_back(&mesh);
        //}

        lPtr = lPtr->GetNext();
    }

    for (auto mat : bindings) {
        RenderData data;
        data.mat = mat.first;
        data.meshes = mat.second;

        _renderData.push_back(data);
    }
}
