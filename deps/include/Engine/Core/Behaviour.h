#pragma once
#include "GameObject.h"

class GameObject;

class Behaviour {
public:
	Behaviour() : obj(nullptr) {}

	GameObject* obj;

	virtual void Init() {}
	virtual void Update() {}

	virtual void OnTransformChanged() {}
};