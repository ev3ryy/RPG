#include <runtime.hpp>

#include <logs.hpp>
#include <pipeline/pipeline.hpp>
#include <scene/scene.hpp>
#include <window/window.hpp>
#include <world/physics_world.hpp>

Runtime::Runtime()
{
    logger::init();
    window = std::make_unique<Window>(1280, 720, "RPG");
    ecsScene = std::make_unique<Scene>();
    physicsWorld = std::make_unique<PhysicsWorld>();

    fixedUpdatePipeline = std::make_unique<Pipeline>();
}

Runtime::~Runtime()
{
}

float Runtime::getDeltaTime()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
    lastTime = currentTime;
    return deltaTime;
}

void Runtime::run()
{
    const float fixedTimeStep = 1.0f / 60.0f;
    float accumulator = 0.0f;

    while (!window->isWindowShouldClose())
    {
        float deltaTime = getDeltaTime();
        accumulator += deltaTime;

        window->pollEvents();

        if (accumulator >= fixedTimeStep)
        {
            // fixedUpdatePipeline->run(ecsScene->get_registry(), fixedTimeStep);
            physicsWorld->run(fixedTimeStep);
            accumulator -= fixedTimeStep;
        }
    }
}