#ifndef PHYSICS_CREATION_SYSTEM_HPP
#define PHYSICS_CREATION_SYSTEM_HPP

#include <components/components.hpp>
#include <components/physics_component.hpp>
#include <pipeline/ISystem.hpp>
#include <world/physics_world.hpp>

#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>

class PhysicsCreationSystem : public ISystem
{
  public:
    PhysicsCreationSystem(PhysicsWorld &physicsWorld);
    ~PhysicsCreationSystem() override = default;

    void update(entt::registry &registry, float dt) override;
    const std::string &getName() const override
    {
        return m_name;
    }

  private:
    PhysicsWorld &m_physicsWorld;
    const std::string m_name = "PhysicsCreationSystem";
};

#endif // PHYSICS_CREATION_SYSTEM_HPP