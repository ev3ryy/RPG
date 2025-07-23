#ifndef ECS_PIPELINE_H
#define ECS_PIPELINE_H

#include <entt/entt.hpp>
#include <functional>
#include <vector>

using System = std::function<void(entt::registry &, float)>;

class Pipeline
{
  public:
    void add_system(System system);
    void run(entt::registry &registry, float dt);

  private:
    std::vector<System> m_systems;
};

#endif // ECS_PIPELINE_H