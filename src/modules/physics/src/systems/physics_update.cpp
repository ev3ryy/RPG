#include <iostream>
#include <systems/physics_update.hpp>

PhysicsUpdateSystem::PhysicsUpdateSystem(PhysicsWorld &physicsWorld) : m_physicsWorld(physicsWorld)
{
}

void PhysicsUpdateSystem::update(entt::registry &registry, float dt)
{
    const int cCollisionSteps = 1;
    m_physicsWorld.getPhysicsSystem().Update(dt, cCollisionSteps, m_physicsWorld.getTempAllocator(),
                                             m_physicsWorld.getJobSystem());

    JPH::BodyInterface &bodyInterface = m_physicsWorld.getPhysicsSystem().GetBodyInterface();

    registry.view<TransformComponent, PhysicsBodyComponent>().each(
        [&](auto entity, TransformComponent &transform, PhysicsBodyComponent &physicsBody) {
            if (bodyInterface.IsActive(physicsBody.body_id))
            {
                JPH::RVec3 position = bodyInterface.GetCenterOfMassPosition(physicsBody.body_id);
                JPH::Quat rotation = bodyInterface.GetRotation(physicsBody.body_id);

                transform.position_x = position.GetX();
                transform.position_y = position.GetY();
                transform.position_z = position.GetZ();

                transform.rotation_x = rotation.GetX();
                transform.rotation_y = rotation.GetY();
                transform.rotation_z = rotation.GetZ();
                transform.rotation_w = rotation.GetW();

                std::cout << "Entity " << static_cast<uint32_t>(entity) << " new pos: (" << transform.position_x << ", "
                          << transform.position_y << ", " << transform.position_z << ")" << std::endl;
            }
        });
}