#ifndef ENGINE_RUNTIME_H
#define ENGINE_RUNTIME_H

#include <chrono>
#include <memory>

class Window;
class Scene;
class Pipeline;
class PhysicsWorld;

class PhysicsCreationSystem;
class PhysicsUpdateSystem;
class PhysicsCleanupSystem;

class Runtime
{
  public:
    Runtime();
    ~Runtime();

    void run();

  private:
    float getDeltaTime();

    std::unique_ptr<Window> window;
    std::unique_ptr<Scene> ecsScene;
    std::unique_ptr<Pipeline> fixedUpdatePipeline;
    std::unique_ptr<PhysicsWorld> physicsWorld;

    std::unique_ptr<PhysicsCreationSystem> physicsCreationSystem;
    std::unique_ptr<PhysicsUpdateSystem> physicsUpdateSystem;
    std::unique_ptr<PhysicsCleanupSystem> physicsCleanupSystem;

    std::chrono::high_resolution_clock::time_point lastTime;
};

#endif // ENGINE_RUNTIME_H
