// GameObject.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>
#include <string>

#include "Identifiable.h"
#include "ComponentRegistry.h"

// Provides easier interaction between components.
class GameObject final : public Identifiable, public std::enable_shared_from_this<GameObject> {
private:
	std::shared_ptr<ComponentRegistry> component_registry;

public:
	GameObject(std::shared_ptr<ComponentRegistry> component_registry);

	std::shared_ptr<ComponentRegistry> GetComponentRegistry();

	std::string tag = "Game Object";

	// Returns this object's component of type ComponentType.
	template<typename ComponentType>
	std::shared_ptr<ComponentType> GetComponent() {
		return this->component_registry->GetComponent<ComponentType>(this->GetID());
	}

	// Adds a component of type ComponentType to this object.
	template<typename ComponentType>
	std::shared_ptr<ComponentType> AddComponent() {
		std::shared_ptr<ComponentType> component = std::make_shared<ComponentType>(this->shared_from_this());
		this->component_registry->RegisterComponent<ComponentType>(this->GetID(), component);
		return component;
	}

	// Unregisters all components associated with this game object.
	void Destroy();
};

