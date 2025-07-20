#include <runtime.hpp>

#include <logs.hpp>
#include <pipeline/pipeline.hpp>
#include <scene/scene.hpp>
#include <window/window.hpp>
#include <world/physics_world.hpp>

#include <systems/physics_cleanup.hpp>
#include <systems/physics_creation.hpp>
#include <systems/physics_update.hpp>

Runtime::Runtime()
{
    logger::init();
    window = std::make_unique<Window>(1280, 720, "RPG");
    ecsScene = std::make_unique<Scene>();
    physicsWorld = std::make_unique<PhysicsWorld>();

    lastTime = std::chrono::high_resolution_clock::now();

    fixedUpdatePipeline = std::make_unique<Pipeline>();

    physicsCreationSystem = std::make_unique<PhysicsCreationSystem>(*physicsWorld);
    physicsUpdateSystem = std::make_unique<PhysicsUpdateSystem>(*physicsWorld);
    physicsCleanupSystem = std::make_unique<PhysicsCleanupSystem>(ecsScene->get_registry(), *physicsWorld);

    fixedUpdatePipeline->add_system([this](entt::registry &reg, float dt) { physicsCreationSystem->update(reg, dt); });

    fixedUpdatePipeline->add_system([this](entt::registry &reg, float dt) { physicsUpdateSystem->update(reg, dt); });

    auto test_entity = ecsScene->create_entity("Dynamic Cube");
    ecsScene->get_registry().emplace<TransformComponent>(test_entity, 0.0f, 5.0f, 0.0f);
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
            fixedUpdatePipeline->run(ecsScene->get_registry(), fixedTimeStep);
            accumulator -= fixedTimeStep;
        }
    }
}