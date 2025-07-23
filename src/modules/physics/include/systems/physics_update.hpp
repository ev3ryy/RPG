#ifndef PHYSICS_UPDATE_SYSTEM_HPP
#define PHYSICS_UPDATE_SYSTEM_HPP

#include <components/components.hpp>
#include <components/physics_component.hpp>
#include <pipeline/ISystem.hpp>
#include <world/physics_world.hpp>

class PhysicsUpdateSystem : public ISystem
{
  public:
    PhysicsUpdateSystem(PhysicsWorld &physicsWorld);
    ~PhysicsUpdateSystem() override = default;

    void update(entt::registry &registry, float dt) override;
    const std::string &getName() const override
    {
        return m_name;
    }

  private:
    PhysicsWorld &m_physicsWorld;
    const std::string m_name = "PhysicsUpdateSystem";
};

#endif // PHYSICS_UPDATE_SYSTEM_HPP