#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

#include <Jolt/Jolt.h>

#include <Jolt/Core/Factory.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/RegisterTypes.h>

#include <cstdarg>
#include <iostream>
#include <thread>

JPH_SUPPRESS_WARNINGS

using namespace JPH;

using namespace JPH::literals;

using namespace std;

static void TraceImpl(const char *inFMT, ...)
{
    va_list list;
    va_start(list, inFMT);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), inFMT, list);
    va_end(list);

    cout << buffer << endl;
}

#ifdef JPH_ENABLE_ASSERTS

static bool AssertFailedImpl(const char *inExpression, const char *inMessage, const char *inFile, uint inLine)
{
    cout << inFile << ":" << inLine << ": (" << inExpression << ") " << (inMessage != nullptr ? inMessage : "") << endl;

    return true;
};

#endif // JPH_ENABLE_ASSERTS

namespace Layers
{
static constexpr ObjectLayer NON_MOVING = 0;
static constexpr ObjectLayer MOVING = 1;
static constexpr ObjectLayer NUM_LAYERS = 2;
}; // namespace Layers

class ObjectLayerPairFilterImpl : public ObjectLayerPairFilter
{
  public:
    virtual bool ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2) const override
    {
        switch (inObject1)
        {
        case Layers::NON_MOVING:
            return inObject2 == Layers::MOVING;
        case Layers::MOVING:
            return true;
        default:
            JPH_ASSERT(false);
            return false;
        }
    }
};

namespace BroadPhaseLayers
{
static constexpr BroadPhaseLayer NON_MOVING(0);
static constexpr BroadPhaseLayer MOVING(1);
static constexpr uint NUM_LAYERS(2);
}; // namespace BroadPhaseLayers

class BPLayerInterfaceImpl final : public BroadPhaseLayerInterface
{
  public:
    BPLayerInterfaceImpl()
    {
        mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
        mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
    }

    virtual uint GetNumBroadPhaseLayers() const override
    {
        return BroadPhaseLayers::NUM_LAYERS;
    }

    virtual BroadPhaseLayer GetBroadPhaseLayer(ObjectLayer inLayer) const override
    {
        JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
        return mObjectToBroadPhase[inLayer];
    }

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
    virtual const char *GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const override
    {
        switch ((BroadPhaseLayer::Type)inLayer)
        {
        case (BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:
            return "NON_MOVING";
        case (BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:
            return "MOVING";
        default:
            JPH_ASSERT(false);
            return "INVALID";
        }
    }
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

  private:
    BroadPhaseLayer mObjectToBroadPhase[Layers::NUM_LAYERS];
};

class ObjectVsBroadPhaseLayerFilterImpl : public ObjectVsBroadPhaseLayerFilter
{
  public:
    virtual bool ShouldCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2) const override
    {
        switch (inLayer1)
        {
        case Layers::NON_MOVING:
            return inLayer2 == BroadPhaseLayers::MOVING;
        case Layers::MOVING:
            return true;
        default:
            JPH_ASSERT(false);
            return false;
        }
    }
};

class MyContactListener : public ContactListener
{
  public:
    virtual ValidateResult OnContactValidate(const Body &inBody1, const Body &inBody2, RVec3Arg inBaseOffset,
                                             const CollideShapeResult &inCollisionResult) override
    {
        cout << "Contact validate callback" << endl;

        return ValidateResult::AcceptAllContactsForThisBodyPair;
    }

    virtual void OnContactAdded(const Body &inBody1, const Body &inBody2, const ContactManifold &inManifold,
                                ContactSettings &ioSettings) override
    {
        cout << "A contact was added" << endl;
    }

    virtual void OnContactPersisted(const Body &inBody1, const Body &inBody2, const ContactManifold &inManifold,
                                    ContactSettings &ioSettings) override
    {
        cout << "A contact was persisted" << endl;
    }

    virtual void OnContactRemoved(const SubShapeIDPair &inSubShapePair) override
    {
        cout << "A contact was removed" << endl;
    }
};

class MyBodyActivationListener : public BodyActivationListener
{
  public:
    virtual void OnBodyActivated(const BodyID &inBodyID, uint64 inBodyUserData) override
    {
        cout << "A body got activated" << endl;
    }

    virtual void OnBodyDeactivated(const BodyID &inBodyID, uint64 inBodyUserData) override
    {
        cout << "A body went to sleep" << endl;
    }
};

class PhysicsWorld
{
  public:
    static constexpr uint cMaxPhysicsJobs = 1024;
    static constexpr uint cMaxPhysicsBarriers = 1024;
    static constexpr uint cMaxBodies = 1024;
    static constexpr uint cNumBodyMutexes = 0;
    static constexpr uint cMaxBodyPairs = 1024;
    static constexpr uint cMaxContactConstraints = 1024;

    PhysicsWorld();
    ~PhysicsWorld();

    void run(float dt);

  private:
    TempAllocatorImpl *temp_allocator;
    JobSystemThreadPool *job_system;
    PhysicsSystem physics_system;

    BPLayerInterfaceImpl broad_phase_layer_interface;
    ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;
    ObjectLayerPairFilterImpl object_vs_object_layer_filter;
    MyBodyActivationListener body_activation_listener;
    MyContactListener contact_listener;

    BodyID floor_id;
    BodyID sphere_id;
};

#endif // PHYSICS_WORLD_H