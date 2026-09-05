#pragma once
#include <PxPhysicsAPI.h>


class PhysicWorld
{
public:
    PhysicWorld();
    ~PhysicWorld();

public:
    bool Initialize();
    void Shutdown();

    void Simulate(float deltaTime);

private:
    physx::PxDefaultAllocator _allocator;
    physx::PxDefaultErrorCallback _errorCallback;

    physx::PxFoundation* _foundation = nullptr;
    physx::PxPhysics* _physics = nullptr;
    physx::PxDefaultCpuDispatcher* _dispatcher = nullptr;
    physx::PxScene* _scene = nullptr;
    physx::PxMaterial* _defaultMaterial = nullptr;
};

