// GameObject.cpp
// Krystof Hruby
// 2023

#include "GameObject.h"

GameObject::GameObject(std::shared_ptr<ComponentRegistry> component_registry) {
	this->component_registry = component_registry;
}

std::shared_ptr<ComponentRegistry> GameObject::GetComponentRegistry() {
	return this->component_registry;
}

