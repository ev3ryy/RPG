#ifndef ECS_ISYSTEM_HPP
#define ECS_ISYSTEM_HPP

#include <entt/entt.hpp>
#include <string>

class ISystem
{
  public:
    virtual ~ISystem() = default;
    virtual void update(entt::registry &registry, float dt) = 0;
    virtual const std::string &getName() const = 0;
};

#endif // ECS_ISYSTEM_HPP