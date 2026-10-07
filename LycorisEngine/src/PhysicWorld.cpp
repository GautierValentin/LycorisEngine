#include <iostream>

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
    _pvd = PxCreatePvd(*_foundation);

    _transport =
        PxDefaultPvdSocketTransportCreate(
            "127.0.0.1", // PVD host
            5425,        // Default port
            10           // Timeout (ms)
        );

    _pvd->connect(
        *_transport,
        physx::PxPvdInstrumentationFlag::eALL
    );

    _physics = PxCreatePhysics(
        PX_PHYSICS_VERSION,
        *_foundation,
        PxTolerancesScale(),
        true,
        _pvd
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

    CreatePhysicsMaterial("default", .5f, .5f, .6f);

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

    return true;
}

void PhysicWorld::Shutdown()
{
    for (auto mat : _physicsMaterials) {
        mat.second->release();
    }
    _physicsMaterials.clear();

    for (auto actor : _actors) {
        actor->release();
    }
    _actors.clear();



    if (_scene)
        _scene->release();
    if (_dispatcher)
        _dispatcher->release();

    PxCloseExtensions();

    if (_physics)
        _physics->release();

    if (_transport)
        _transport->release();
    if (_pvd)
        _pvd->release();

    if (_foundation)
        _foundation->release();


    _scene = nullptr;
    _dispatcher = nullptr;
    _physics = nullptr;
    _foundation = nullptr;
    _pvd = nullptr;
    _transport = nullptr;
}

void PhysicWorld::Simulate(float deltaTime)
{
    _scene->simulate(deltaTime);
    _scene->fetchResults(true);
}

bool PhysicWorld::CreatePhysicsMaterial(const char* name, float staticFriction, float dynamicFriction, float restitution)
{
    if (_physicsMaterials.contains(name))
        return false;

    PxMaterial* mat = _physics->createMaterial(staticFriction, dynamicFriction, restitution);
    _physicsMaterials[name] = mat;

    return true;
}

physx::PxRigidActor* PhysicWorld::CreateActor(PxTransform transform, physx::PxGeometry* geometry, const char* physicsMaterial, BodyType bodyType)
{
    PxRigidActor* actor;

    switch (bodyType) {
    case STATIC_BODY:
        actor = _physics->createRigidStatic(transform);
        break;
    case DYNAMIC_BODY:
        actor = _physics->createRigidDynamic(transform);
        break;
    default:
        throw std::exception("Impossible body type");
    }

    PxMaterial* material = GetPhysicsMaterial(physicsMaterial);
    PxShape* shape = _physics->createShape(*geometry, *material);

    actor->attachShape(*shape);

    _scene->addActor(*actor);

    _actors.push_back(actor);

    return actor;
}

physx::PxMaterial* PhysicWorld::GetPhysicsMaterial(const char* name)
{
    return _physicsMaterials[name];
}
