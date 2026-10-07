#pragma once
#include <map>
#include <vector>
#include <PxPhysicsAPI.h>

enum BodyType {
    STATIC_BODY,
    DYNAMIC_BODY,
};


class PhysicWorld
{
public:
    PhysicWorld();
    ~PhysicWorld();

public:
    bool Initialize();
    void Shutdown();

    void Simulate(float deltaTime);

public:
    bool CreatePhysicsMaterial(const char* name, float staticFriction, float dynamicFriction, float restitution);
    physx::PxRigidActor* CreateActor(physx::PxTransform transform, physx::PxGeometry* geometry, const char* physicsMaterial, BodyType bodyType);

public:
    physx::PxMaterial* GetPhysicsMaterial(const char* name);

private:
    physx::PxDefaultAllocator _allocator;
    physx::PxDefaultErrorCallback _errorCallback;

    physx::PxFoundation* _foundation = nullptr;
    physx::PxPhysics* _physics = nullptr;
    physx::PxDefaultCpuDispatcher* _dispatcher = nullptr;
    physx::PxScene* _scene = nullptr;

    physx::PxPvd* _pvd;
    physx::PxPvdTransport* _transport;

private:
    std::map<const char*, physx::PxMaterial*> _physicsMaterials;
    std::vector<physx::PxActor*> _actors;
};

