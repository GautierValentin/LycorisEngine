#include <iostream>
#include "OtherShoreApp.h"

int main()
{
    OtherShoreApp app;

    app.Init(640, 420);

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