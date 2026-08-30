#include <iostream>
#include <glm/glm.hpp>

#include "Application.h"

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

    Entity* entity = _scene->Add();
    Entity* entity2 = _scene->Add();

    MaterialDesc matDesc;
    matDesc.renderer = _renderer;
    matDesc.texturePath = "textures/emi.png";
    Material mat(matDesc);

    MeshRendererDesc mrDesc;
    mrDesc.meshRef = &hand;
    mrDesc.material = &mat;


    MaterialDesc matDesc2;
    matDesc2.renderer = _renderer;
    matDesc2.texturePath = "textures/yay.png";
    Material mat2(matDesc2);

    MeshRendererDesc mrDesc2;
    mrDesc2.meshRef = &bonsho;
    mrDesc2.material = &mat2;

    entity->AddComponent(mrDesc);
    entity2->AddComponent(mrDesc2);

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
    while (false == glfwWindowShouldClose(_win)) {
        
        glfwPollEvents();
        auto data = _scene->Update();
        _renderer->DrawFrame(data);
    }
}