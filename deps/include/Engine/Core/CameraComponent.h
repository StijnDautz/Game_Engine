#pragma once
#include "Behaviour.h"
#include "Transform.h"

class CameraComponent : public Behaviour {
public:
	CameraComponent(glm::mat4 projection) : _projection(projection) {}
	~CameraComponent() {}

	glm::mat4 toScreen;

	void Init() override {
		ComputeToScreen();
	}

	void OnTransformChanged() override {
		ComputeToScreen();
	}

	void SetPerspective(glm::mat4 p) {
		_projection = p;
		ComputeToScreen();
	}

private:
	glm::mat4 _projection;

	void ComputeToScreen() {
		glm::mat4 worldpos = obj->GetComponent<Transform>()->GetWorldMatrix();
		toScreen = worldpos * _projection;
	}
};