#ifndef PHYSICS_CLEANUP_SYSTEM_HPP
#define PHYSICS_CLEANUP_SYSTEM_HPP

#include <entt/entt.hpp>

#include <components/physics_component.hpp>
#include <world/physics_world.hpp>

class PhysicsCleanupSystem
{
  public:
    PhysicsCleanupSystem(entt::registry &registry, PhysicsWorld &physicsWorld);
    ~PhysicsCleanupSystem();

  private:
    PhysicsWorld &m_physicsWorld;

    // Ссылка на соединение с событием on_destroy
    entt::connection m_connection;

    // Метод, который будет вызываться при уничтожении сущности с PhysicsBodyComponent
    void onBodyDestroyed(entt::registry &registry, entt::entity entity);
};

#endif // PHYSICS_CLEANUP_SYSTEM_HPP