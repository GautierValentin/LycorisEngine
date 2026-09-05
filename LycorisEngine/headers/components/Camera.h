#pragma once
#include <glm/matrix.hpp>

#include "Component.h"

struct CameraDesc;

class Camera : public Component
{
public:
	Camera(CameraDesc desc);
	~Camera();

	void Update() override;

	glm::mat4 ComputeViewMatrix();

private:
	int _mandatoryIntidk;
};

struct CameraDesc {
	using ComponentType = Camera;
	Entity* entity;
};