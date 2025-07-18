#include <runtime.hpp>

#include <logs.hpp>
#include <window/window.hpp>

Runtime::Runtime()
{
    window = std::make_unique<Window>(1280, 720, "RPG");
}

Runtime::~Runtime()
{
}

void Runtime::run()
{
    while (!window->isWindowShouldClose())
    {
        window->pollEvents();
    }
}