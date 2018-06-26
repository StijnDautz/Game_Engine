#pragma once
#include "Behaviour.h"

#include <map>
#include <typeinfo>

class Behaviour;

class GameObject
{
typedef std::map<const char*, Behaviour*> BehaviourMap;

public:
	GameObject();
	~GameObject() {}

	template <class T>
	void AddComponent(T* b) {
		static_assert(std::is_base_of<Behaviour, T>::value, "type parameter of this class must derive from BaseClass");

		_components.insert(std::make_pair(typeid(b).name(), b));
		b->obj = this;
		b->Init();
	}
	template <class T>
	void RemoveComponent() {
		static_assert(std::is_base_of<Behaviour, T>::value, "type parameter of this class must derive from BaseClass");
		
		_components.erase(typeid(T*).name());
	}
	template <class T>
	T* GetComponent() {
		static_assert(std::is_base_of<Behaviour, T>::value, "type parameter of this class must derive from BaseClass");
		return (T*)_components.at(typeid(T*).name());
	}

	void Update();
	void OnMovement();

private:
	BehaviourMap _components;
};