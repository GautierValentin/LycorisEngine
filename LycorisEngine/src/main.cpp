#include <iostream>
#include <glm/glm.hpp>
#include "Application.h"

int main() {
    Application app;

    app.Init(640, 420);

    Entity* entity = app._scene->Add();
    MeshRendererDesc mDesc;
    entity->AddComponent(mDesc);

    try {
        app.Run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    app.UnInit();

    return 0;
}