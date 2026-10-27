#include <iostream>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <GLFW/glfw3.h>
#include <chrono>
#include <PxPhysics.h>

#include "HiganApp.h"

#include "components/Script.h"
#include "components/Collider.h"
#include "components/Light.h"


HiganApp::HiganApp()
{
    //Init();
}

HiganApp::~HiganApp()
{
    //UnInit();
}

int HiganApp::Init(uint32_t width, uint32_t height)
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

    Start();

    return 0;
}

int HiganApp::UnInit()
{
    delete _allocator;

    delete _scene;

    _renderer->UnInit();
    delete _renderer;

    return 0;
}

void HiganApp::Run()
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


