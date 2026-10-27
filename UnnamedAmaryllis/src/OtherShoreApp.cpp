#include "PhysicWorld.h"
#include "test.h"
#include "components/Camera.h"
#include "components/Collider.h"
#include "components/Light.h"
#include "components/MeshRenderer.h"
#include "components/Transform.h"

#include "OtherShoreApp.h"

OtherShoreApp::OtherShoreApp() : HiganApp()
{
}

OtherShoreApp::~OtherShoreApp()
{
}

void OtherShoreApp::Start()
{
    // Starting les betises

    MeshRef& hand = _allocator->LoadMesh("C:/Users/Utilisateur/source/repos/LycorisEngine/LycorisEngine/models/SubdividedHand.obj", "hand", MeshType::STATIC, _loadedMeshes);
    MeshRef& bonsho = _allocator->LoadMesh("C:/Users/Utilisateur/source/repos/LycorisEngine/LycorisEngine/models/Bonsho.obj", "bonsho", MeshType::STATIC, _loadedMeshes);

    TransformDesc tDesc;
    tDesc.position = glm::vec3(0, 0, 0);
    Entity* entity = _scene->Add(tDesc);

    MaterialDesc matDesc;
    matDesc.renderer = _renderer;
    matDesc.texturePath = "C:/Users/Utilisateur/source/repos/LycorisEngine/LycorisEngine/textures/emi.png";
    Material mat(matDesc);

    MeshRendererDesc mrDesc;
    mrDesc.meshRef = &hand;
    mrDesc.material = &mat;

    entity->AddComponent(mrDesc);

    ColliderDesc colDesc;
    colDesc.scene = _scene;
    physx::PxBoxGeometry cubeGeo = physx::PxBoxGeometry(1, 1, 2);
    colDesc.geometry = &cubeGeo;
    colDesc.physicsMaterial = "default";
    colDesc.bodyType = BodyType::DYNAMIC_BODY;

    entity->AddComponent(colDesc);

    _entity = entity;


    TransformDesc tDesc2;
    tDesc2.position = glm::vec3(1, 0, 1);
    tDesc2.parent = entity->GetTransform();
    Entity* entity2 = _scene->Add(tDesc2);

    MaterialDesc matDesc2;
    matDesc2.renderer = _renderer;
    matDesc2.texturePath = "C:/Users/Utilisateur/source/repos/LycorisEngine/LycorisEngine/textures/yay.png";
    Material mat2(matDesc2);

    MeshRendererDesc mrDesc2;
    mrDesc2.meshRef = &hand;
    mrDesc2.material = &mat2;

    entity2->AddComponent(mrDesc2);

    _entity2 = entity2;



    TransformDesc tDescCam;
    tDescCam.position = glm::vec3(0, -1, 0);
    tDescCam.rotation = glm::quat(glm::vec3(0, 0, 0));
    _cam = _scene->Add(tDescCam);
    _scene->SetCamera(_cam);

    MaterialDesc matDesc3;
    matDesc3.renderer = _renderer;
    matDesc3.texturePath = "C:/Users/Utilisateur/source/repos/LycorisEngine/LycorisEngine/textures/emi.png";
    Material mat3(matDesc3);

    MeshRendererDesc mrDesc3;
    mrDesc3.meshRef = &bonsho;
    mrDesc3.material = &mat3;

    Entity* light = _scene->Add(tDesc);
    LightDesc lDesc;
    lDesc.color = glm::vec3(1, 1, 1);
    lDesc.direction = glm::vec3(0, 1, 0);

    light->AddComponent(lDesc);
    light->AddComponent(mrDesc3);
    _scene->SetLight(light);







    TransformDesc tDescGround;
    tDescGround.position = glm::vec3(0, -6, 0);
    Entity* ground = _scene->Add(tDescGround);

    ColliderDesc colDescGround;
    colDescGround.scene = _scene;
    physx::PxBoxGeometry planeGeo = physx::PxBoxGeometry(4, 1, 4);
    colDescGround.geometry = &planeGeo;
    colDescGround.physicsMaterial = "default";
    colDescGround.bodyType = BodyType::STATIC_BODY;

    ground->AddComponent(colDescGround);

    ScriptDesc sDesc;
    sDesc.window = _win;
    CustomScriptDesc csDesc;
    csDesc.desc = sDesc;
    csDesc._entity = entity;
    csDesc._entity2 = entity2;
    csDesc._entity3 = light;

    _cam->AddComponent(csDesc);

    glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
