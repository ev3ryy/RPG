#ifndef COMPONENTS_PHYSICS_COMPONENTS_HPP
#define COMPONENTS_PHYSICS_COMPONENTS_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyID.h>
#include <Jolt/Physics/Body/MotionType.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct PhysicsBodyComponent
{
    JPH::BodyID body_id;
    JPH::Body *body_ptr;

    enum class BodyType
    {
        Static,
        Dynamic,
        Kinematic
    };
    BodyType type;

    PhysicsBodyComponent() = default;

    PhysicsBodyComponent(JPH::BodyID id, JPH::Body *ptr, BodyType t) : body_id(id), body_ptr(ptr), type(t)
    {
    }
};

#endif // COMPONENTS_PHYSICS_COMPONENTS_HPP
