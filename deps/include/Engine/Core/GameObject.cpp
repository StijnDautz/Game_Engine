#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject() {
	AddComponent(new Transform());
}

void GameObject::Update()
{
	for (BehaviourMap::iterator i = _components.begin(); i != _components.end(); i++) {
		i->second->OnTransformChanged();
	}
}

void GameObject::OnMovement()
{
	for (BehaviourMap::iterator i = _components.begin(); i != _components.end(); i++) {
		i->second->OnTransformChanged();
	}
}