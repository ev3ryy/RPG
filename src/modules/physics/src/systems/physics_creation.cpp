#include <iostream>
#include <systems/physics_creation.hpp>

PhysicsCreationSystem::PhysicsCreationSystem(PhysicsWorld &physicsWorld) : m_physicsWorld(physicsWorld)
{
}

void PhysicsCreationSystem::update(entt::registry &registry, float dt)
{
    registry.view<TransformComponent>(entt::exclude<PhysicsBodyComponent>)
        .each([&](auto entity, TransformComponent &transform) {
            JPH::BoxShapeSettings boxShapeSettings(JPH::Vec3(0.5f, 0.5f, 0.5f));
            boxShapeSettings.SetEmbedded();
            JPH::ShapeSettings::ShapeResult boxShapeResult = boxShapeSettings.Create();
            JPH::ShapeRefC boxShape = boxShapeResult.Get();

            JPH::RVec3 initialPos(transform.position_x, transform.position_y, transform.position_z);
            JPH::Quat initialRot = JPH::Quat::sIdentity();

            JPH::BodyCreationSettings bodySettings(boxShape, initialPos, initialRot, JPH::EMotionType::Dynamic,
                                                   Layers::MOVING);

            JPH::BodyInterface &bodyInterface = m_physicsWorld.getPhysicsSystem().GetBodyInterface();
            JPH::Body *body = bodyInterface.CreateBody(bodySettings);

            body->SetUserData(static_cast<uint64>(entity));

            bodyInterface.AddBody(body->GetID(), JPH::EActivation::Activate);

            registry.emplace<PhysicsBodyComponent>(entity, body->GetID(), body,
                                                   PhysicsBodyComponent::BodyType::Dynamic);

            std::cout << "PhysicsCreationSystem: Created Jolt Body for entity " << static_cast<uint32_t>(entity)
                      << " at (" << transform.position_x << ", " << transform.position_y << ", " << transform.position_z
                      << ")" << std::endl;
        });
}