#include <iostream>
#include <systems/physics_cleanup.hpp>

PhysicsCleanupSystem::PhysicsCleanupSystem(entt::registry &registry, PhysicsWorld &physicsWorld)
    : m_physicsWorld(physicsWorld)
{
    m_connection = registry.on_destroy<PhysicsBodyComponent>().connect<&PhysicsCleanupSystem::onBodyDestroyed>(*this);
    std::cout << "PhysicsCleanupSystem: Subscribed to PhysicsBodyComponent destruction events." << std::endl;
}

PhysicsCleanupSystem::~PhysicsCleanupSystem()
{
    m_connection = {};
    std::cout << "PhysicsCleanupSystem: Unsubscribed from PhysicsBodyComponent destruction events." << std::endl;
}

void PhysicsCleanupSystem::onBodyDestroyed(entt::registry &registry, entt::entity entity)
{
    const auto &physicsBody = registry.get<PhysicsBodyComponent>(entity);

    JPH::BodyInterface &bodyInterface = m_physicsWorld.getPhysicsSystem().GetBodyInterface();

    bodyInterface.RemoveBody(physicsBody.body_id);
    bodyInterface.DestroyBody(physicsBody.body_id);

    std::cout << "PhysicsCleanupSystem: Removed and destroyed Jolt Body for entity " << static_cast<uint32_t>(entity)
              << std::endl;
}