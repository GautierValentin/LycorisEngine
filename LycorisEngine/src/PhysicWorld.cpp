#include "PhysicWorld.h"

using namespace physx;

PhysicWorld::PhysicWorld()
{
}

PhysicWorld::~PhysicWorld()
{
}

bool PhysicWorld::Initialize()
{
    _foundation = PxCreateFoundation(
        PX_PHYSICS_VERSION,
        _allocator,
        _errorCallback
    );

    //if (false == _foundation)
    //    return false;

#ifdef _DEBUG
    physx::PxPvd* pvd = PxCreatePvd(*_foundation);

    physx::PxPvdTransport* transport =
        PxDefaultPvdSocketTransportCreate(
            "127.0.0.1", // PVD host
            5425,        // Default port
            10           // Timeout (ms)
        );

    pvd->connect(
        *transport,
        physx::PxPvdInstrumentationFlag::eALL
    );

    _physics = PxCreatePhysics(
        PX_PHYSICS_VERSION,
        *_foundation,
        PxTolerancesScale(),
        true,
        pvd
    );

#else

    _physics = PxCreatePhysics(
        PX_PHYSICS_VERSION,
        *_foundation,
        PxTolerancesScale()
    );

#endif

    //if (false == _physics)
    //    return false;

    PxSceneDesc sceneDesc(_physics->getTolerancesScale());

    sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);

   _dispatcher = PxDefaultCpuDispatcherCreate(2);

    //if (false == _dispatcher)
    //    return false;

    sceneDesc.cpuDispatcher = _dispatcher;
    sceneDesc.filterShader = PxDefaultSimulationFilterShader;


    _scene = _physics->createScene(sceneDesc);

    //if (false == _scene)
    //    return false;

    _defaultMaterial = _physics->createMaterial(
        0.5f, // static friction
        0.5f, // dynamic friction
        0.6f  // restitution
    );

#ifdef _DEBUG
    PxPvdSceneClient* pvdClient =
        _scene->getScenePvdClient();

    if (pvdClient)
    {
        pvdClient->setScenePvdFlags(
            PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS |
            PxPvdSceneFlag::eTRANSMIT_CONTACTS |
            PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES
        );
    }
#endif


    PxTransform transform(
        PxVec3(0.0f, 5.0f, 0.0f)
    );

    PxRigidDynamic* actor =
        _physics->createRigidDynamic(transform);

    PxShape* shape =
        _physics->createShape(
            PxBoxGeometry(0.5f, 0.5f, 0.5f),
            *_defaultMaterial
        );

    actor->attachShape(*shape);


    return _defaultMaterial != nullptr;
}

void PhysicWorld::Shutdown()
{
    if (_scene)
        _scene->release();
    if (_dispatcher)
        _dispatcher->release();
    if (_physics)
        _physics->release();
    if (_foundation)
        _foundation->release();
    _scene = nullptr;
    _dispatcher = nullptr;
    _physics = nullptr;
    _foundation = nullptr;

}

void PhysicWorld::Simulate(float deltaTime)
{
    _scene->simulate(deltaTime);
    _scene->fetchResults(true);
}
