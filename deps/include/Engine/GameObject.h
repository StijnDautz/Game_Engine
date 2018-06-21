#pragma once
#include "Transform.h"
#include "Renderer.h"
#include "Behaviour.h"

#include <vector>

class GameObject
{
public:
	GameObject() : renderComponent(RenderComponent()) {}
	~GameObject() {}

	Transform transform;
	RenderComponent renderComponent;

	void AddComponent(Behaviour b){
		_components.push_back(b);
		b.Init();
	}

	void Update() {
		for (unsigned int i = 0; i < _components.size(); i++) {
			_components[i].Update();
		}
	}

private:
	std::vector<Behaviour> _components;
};