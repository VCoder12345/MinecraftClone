#pragma once

#include <map>
#include <typeindex>

#include <iostream>
#include <string>

#include "Component.h"

class Entity {
public:
	std::string name;

	Entity(std::string name) : name(name) {}

	~Entity();

	template<class T>
	void addComponent(T* component) {
		components[typeid(T)] = component;
	}

	template<class T>
	T& getComponent() {
		return *static_cast<T*>(components[typeid(T)]);
	}

	template<class T, class... Args>
	bool hasComponent() {
		if constexpr(sizeof...(Args) == 0) {
			return components.find(typeid(T)) != components.end();
		}
		else {
			return hasComponent<T>() && hasComponent<Args...>();
		}
	}

	

private:
	std::map<std::type_index, Component*> components;
	
};