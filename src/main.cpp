#include "game/app/Application.hpp"

#include <exception>
#include <iostream>

int main()
{
    try {
        gameapp::Application application;
        return application.run();
    } catch (const std::exception& exception) {
        std::cerr << "Fatal error: " << exception.what() << '\n';
        return 1;
    }
}
