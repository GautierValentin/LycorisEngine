#include <map>
#include <glm/glm.hpp>

#include "components/Camera.h"
#include "components/Light.h"
#include "Scene.h"

Scene::Scene() : _camera(nullptr)
{
    _meshRenderers_ll = new LinkPtr<Entity>(nullptr, nullptr, nullptr);
    _entities.reserve(8);

    _physicWorld = new PhysicWorld();
    _physicWorld->Initialize();
}

Scene::~Scene()
{
    _physicWorld->Shutdown();
    delete _physicWorld;

    _meshRenderers_ll->DeleteList();
}

std::vector<RenderData> Scene::Update(float deltaTime)
{
    UpdateEntitesComponentsReferences();
    PackRenderData();

    _physicWorld->Simulate(deltaTime);

    for (Entity& entity : _entities)
        entity.Update();

    return _renderData;
}

void Scene::UpdateEntitesComponentsReferences()
{
    for (Entity* entity : _needUpdateEntities) {
        entity->_needUpdate = false;

        if (entity->Contains<MeshRenderer>()) {
            if (false == _meshRenderers_ll->Contains(entity)) {
                _meshRenderers_ll->Add(entity);
            }
        }
    }
    _needUpdateEntities.clear();
}

Entity* Scene::Add(TransformDesc desc)
{
    std::function<void(Entity*)> func = [this](Entity* self) {this->_needUpdateEntities.push_back(self); };

    Entity& entity = _entities.emplace_back(func);

    /*if (desc.parent != nullptr)
        if (std::find(_entities.begin(), _entities.end(), *(desc.parent)) == _entities.end())
            throw std::runtime_error("the provided parent is not in the scene");*/

    entity.AddComponent(desc);
    entity.AssignTransform();
    

    return &entity;
}

Entity* Scene::SetCamera(Entity* entity)
{
    if (_camera != nullptr)
        throw std::runtime_error("there is already a camera in the scene");

    Camera* cam;
    if (false == entity->TryFind(cam)) {
        CameraDesc desc = CameraDesc();
        entity->AddComponent(desc);
    }

    _camera = entity;
}

glm::mat4 Scene::GetCamView()
{
#ifdef _DEBUG
    if (_camera == nullptr)
        throw std::runtime_error("there is no camera in the scene");
#endif

    Camera* cam;
    _camera->TryFind(cam);

    return cam->ComputeViewMatrix();
}

Entity* Scene::SetLight(Entity* entity)
{
    if (_light != nullptr)
        throw std::runtime_error("there is already a camera in the scene");

    Camera* cam;
    if (false == entity->TryFind(cam)) {
        CameraDesc desc = CameraDesc();
        entity->AddComponent(desc);
    }

    _light = entity;
}

std::pair<glm::vec3, glm::vec3> Scene::GetLightData()
{
#ifdef _DEBUG
    if (_light == nullptr)
        throw std::runtime_error("there is no light in the scene");
#endif

    Light* light;
    _light->TryFind(light);

    std::pair<glm::vec3, glm::vec3> pair;
    pair.first = light->ComputeDirection();
    pair.second = light->GetColor();

    return pair;
}

// Distribute specific components ref into dedicated virtual arrays
void Scene::PackRenderData()
{
    if (_meshRenderers_ll == nullptr)
        return;

    _renderData.clear();

    std::map<Material*, std::pair<std::vector<MeshRef*>, std::vector<glm::mat4>>> bindings;

    LinkPtr<Entity>* lPtr = _meshRenderers_ll;
    while (lPtr != nullptr && lPtr->GetRef() != nullptr) {
        MeshRenderer* mr;
        lPtr->GetRef()->TryFind(mr);
        Material& mat = mr->_mat;
        MeshRef& mesh = mr->_mesh;

        Transform* tr;
        lPtr->GetRef()->TryFind(tr);
        glm::mat4 model = tr->ComputeWorldMatrix();

        bindings[&mat].first.push_back(&mesh);
        bindings[&mat].second.push_back(model);

        lPtr = lPtr->GetNext();
    }

    for (auto mat : bindings) {
        RenderData data;
        data.mat = mat.first;
        data.meshes = mat.second.first;
        data.models = mat.second.second;

        _renderData.push_back(data);
    }
}
