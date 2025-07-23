#include <world/physics_world.hpp>

PhysicsWorld::PhysicsWorld()
    : broad_phase_layer_interface(), object_vs_broadphase_layer_filter(), object_vs_object_layer_filter(),
      body_activation_listener(), contact_listener()
{
    RegisterDefaultAllocator();

    Trace = TraceImpl;
    JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)

    Factory::sInstance = new Factory();

    RegisterTypes();

    temp_allocator = new TempAllocatorImpl(10 * 1024 * 1024);
    job_system = new JobSystemThreadPool(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);

    physics_system.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, broad_phase_layer_interface,
                        object_vs_broadphase_layer_filter, object_vs_object_layer_filter);

    physics_system.SetBodyActivationListener(&body_activation_listener);
    physics_system.SetContactListener(&contact_listener);

    BodyInterface &body_interface = physics_system.GetBodyInterface();

    BoxShapeSettings floor_shape_settings(Vec3(100.0f, 1.0f, 100.0f));
    floor_shape_settings.SetEmbedded();
    ShapeSettings::ShapeResult floor_shape_result = floor_shape_settings.Create();
    ShapeRefC floor_shape = floor_shape_result.Get();

    BodyCreationSettings floor_settings(floor_shape, RVec3(0.0_r, -1.0_r, 0.0_r), Quat::sIdentity(),
                                        EMotionType::Static, Layers::NON_MOVING);
    Body *floor = body_interface.CreateBody(floor_settings);
    floor_id = floor->GetID();
    body_interface.AddBody(floor_id, EActivation::DontActivate);

    BodyCreationSettings sphere_settings(new SphereShape(0.5f), RVec3(0.0_r, 2.0_r, 0.0_r), Quat::sIdentity(),
                                         EMotionType::Dynamic, Layers::MOVING);
    sphere_id = body_interface.CreateAndAddBody(sphere_settings, EActivation::Activate);

    body_interface.SetLinearVelocity(sphere_id, Vec3(0.0f, -5.0f, 0.0f));

    physics_system.OptimizeBroadPhase();
}

PhysicsWorld::~PhysicsWorld()
{
    BodyInterface &body_interface = physics_system.GetBodyInterface();
    body_interface.RemoveBody(sphere_id);
    body_interface.DestroyBody(sphere_id);
    body_interface.RemoveBody(floor_id);
    body_interface.DestroyBody(floor_id);

    UnregisterTypes();
    delete Factory::sInstance;
    Factory::sInstance = nullptr;

    delete job_system;
    delete temp_allocator;
}

void PhysicsWorld::run(float dt)
{
    const int cCollisionSteps = 1;
    physics_system.Update(dt, cCollisionSteps, temp_allocator, job_system);

    BodyInterface &body_interface = physics_system.GetBodyInterface();
    if (body_interface.IsActive(sphere_id))
    {
        RVec3 position = body_interface.GetCenterOfMassPosition(sphere_id);
        Vec3 velocity = body_interface.GetLinearVelocity(sphere_id);
        cout << "Position = (" << position.GetX() << ", " << position.GetY() << ", " << position.GetZ()
             << "), Velocity = (" << velocity.GetX() << ", " << velocity.GetY() << ", " << velocity.GetZ() << ")"
             << endl;
    }
    else
    {
        cout << "Sphere is sleeping or inactive." << endl;
    }
}