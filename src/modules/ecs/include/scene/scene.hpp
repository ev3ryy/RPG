#ifndef ECS_SCENE_H
#define ECS_SCENE_H

#include <entt/entt.hpp>

class Scene
{
  public:
    Scene() = default;
    ~Scene() = default;

    entt::entity create_entity(const std::string &name = "Entity");

    entt::registry &get_registry()
    {
        return m_registry;
    }
    const entt::registry &get_registry() const
    {
        return m_registry;
    }

  private:
    entt::registry m_registry;
};

#endif // ECS_SCENE_H