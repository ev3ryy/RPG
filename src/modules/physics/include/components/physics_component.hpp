#ifndef COMPONENTS_PHYSICS_COMPONENTS_HPP
#define COMPONENTS_PHYSICS_COMPONENTS_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyID.h>
#include <Jolt/Physics/Body/MotionType.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace JPH
{
class Shape;
class Body;
class BodyInterface;
class PhysicsSystem;
} // namespace JPH

struct RigidBodyComponent
{
    JPH::BodyID bodyID = JPH::BodyID();
    JPH::EMotionType motionType = JPH::EMotionType::Dynamic;
    float mass = 1.0f;
    glm::vec3 linearVelocity = glm::vec3(0.0f);
    glm::vec3 angularVelocity = glm::vec3(0.0f);
    bool isAddedToPhysicsWorld = false;

    RigidBodyComponent() = default;

    RigidBodyComponent(JPH::EMotionType type, float m = 1.0f) : motionType(type), mass(m)
    {
    }
};

struct ColliderComponent
{
    JPH::ShapeRefC shape;

    ColliderComponent() = default;

    ColliderComponent(JPH::ShapeRefC s) : shape(s)
    {
    }

    ColliderComponent(const glm::vec3 &halfExtent)
    {
        shape = new JPH::BoxShape(JPH::Vec3(halfExtent.x, halfExtent.y, halfExtent.z));
    }
};

#endif // COMPONENTS_PHYSICS_COMPONENTS_HPP
