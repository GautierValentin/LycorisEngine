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

    _renderer = std::make_unique<Renderer>();
    _renderer->Init(_win);

    return 0;
}

int Application::UnInit()
{
    _renderer->UnInit();
    delete _renderer.release();

    return 0;
}

void Application::Run()
{
    while (false == glfwWindowShouldClose(_win)) {
        
        glfwPollEvents();
        _scene->Update();
        _renderer->Tick();
    }
}
