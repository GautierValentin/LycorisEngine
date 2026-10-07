#include <iostream>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <GLFW/glfw3.h>
#include <chrono>
#include <PxPhysics.h>

#include "Application.h"

#include "components/Script.h"
#include "components/Collider.h"
#include "components/Light.h"
#include "test.h"


Application::Application()
{
    //Init();
}

Application::~Application()
{
    //UnInit();
}

int Application::Init(uint32_t width, uint32_t height)
{
    _scene = new Scene();

    if (false == glfwInit())
        return -1;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);


    _win = glfwCreateWindow(width, height, "Courage!", NULL, NULL);

    glfwSetWindowUserPointer(_win, this);
    if (!_win)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(_win);

    _renderer = new Renderer();
    _renderer->Init(_win);

    _allocator = new ResourcesAllocator(_renderer);

    // Starting les betises

    MeshRef& hand = _allocator->LoadMesh("models/SubdividedHand.obj", "hand", MeshType::STATIC, _loadedMeshes);
    MeshRef& bonsho = _allocator->LoadMesh("models/Bonsho.obj", "bonsho", MeshType::STATIC, _loadedMeshes);

    TransformDesc tDesc;
    tDesc.position = glm::vec3(0, 0, 0);
    Entity* entity = _scene->Add(tDesc);

    MaterialDesc matDesc;
    matDesc.renderer = _renderer;
    matDesc.texturePath = "textures/emi.png";
    Material mat(matDesc);

    MeshRendererDesc mrDesc;
    mrDesc.meshRef = &hand;
    mrDesc.material = &mat;

    entity->AddComponent(mrDesc);

    ColliderDesc colDesc;
    colDesc.scene = _scene;
    physx::PxBoxGeometry cubeGeo = physx::PxBoxGeometry(1, 1, 2);
    colDesc.geometry = &cubeGeo;
    colDesc.physicsMaterial = "default";
    colDesc.bodyType = BodyType::DYNAMIC_BODY;

    entity->AddComponent(colDesc);

    _entity = entity;


    TransformDesc tDesc2;
    tDesc2.position = glm::vec3(1, 0, 1);
    tDesc2.parent = entity->GetTransform();
    Entity* entity2 = _scene->Add(tDesc2);

    MaterialDesc matDesc2;
    matDesc2.renderer = _renderer;
    matDesc2.texturePath = "textures/yay.png";
    Material mat2(matDesc2);

    MeshRendererDesc mrDesc2;
    mrDesc2.meshRef = &hand;
    mrDesc2.material = &mat2;

    entity2->AddComponent(mrDesc2);

    _entity2 = entity2;



    TransformDesc tDescCam;
    tDescCam.position = glm::vec3(0, -1, 0);
    tDescCam.rotation = glm::quat(glm::vec3(90, 0, 0));
    _cam = _scene->Add(tDescCam);
    _scene->SetCamera(_cam);
    
    MaterialDesc matDesc3;
    matDesc3.renderer = _renderer;
    matDesc3.texturePath = "textures/emi.png";
    Material mat3(matDesc3);

    MeshRendererDesc mrDesc3;
    mrDesc3.meshRef = &bonsho;
    mrDesc3.material = &mat3;

    Entity* light = _scene->Add(tDesc);
    LightDesc lDesc;
    lDesc.color = glm::vec3(1, 1, 1);
    lDesc.direction = glm::vec3(0, 1, 0);

    light->AddComponent(lDesc);
    light->AddComponent(mrDesc3);
    _scene->SetLight(light);


    

    


    TransformDesc tDescGround;
    tDescGround.position = glm::vec3(0, -6, 0);
    Entity* ground = _scene->Add(tDescGround);

    ColliderDesc colDescGround;
    colDescGround.scene = _scene;
    physx::PxBoxGeometry planeGeo = physx::PxBoxGeometry(4, 1, 4);
    colDescGround.geometry = &planeGeo;
    colDescGround.physicsMaterial = "default";
    colDescGround.bodyType = BodyType::STATIC_BODY;

    ground->AddComponent(colDescGround);

    ScriptDesc sDesc;
    sDesc.window = _win;
    CustomScriptDesc csDesc;
    csDesc.desc = sDesc;
    csDesc._entity = entity;
    csDesc._entity2 = entity2;
    csDesc._entity3 = light;

    _cam->AddComponent(csDesc);

    glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return 0;
}

int Application::UnInit()
{
    delete _allocator;

    delete _scene;

    _renderer->UnInit();
    delete _renderer;

    return 0;
}

void Application::Run()
{
    auto last = std::chrono::steady_clock::now();
    const float fixedDT = 1.0f / 60.0f;
    float accumulator = 0.0f;

    while (false == glfwWindowShouldClose(_win)) {
        
        glfwPollEvents();

        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> delta = now - last;
        last = now;
        auto dt = delta.count();

        // TEMP

        

        //END TEMP

        auto data = _scene->Update(dt);
        auto view = _scene->GetCamView();
        auto lightPair = _scene->GetLightData();
        _renderer->DrawFrame(data, view, lightPair.first, lightPair.second);
    }
}


