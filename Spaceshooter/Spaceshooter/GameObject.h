// GameObject.h
// Krystof Hruby
// 2023

#pragma once

#include "ComponentRegistry.h"

// Provides easier interaction between components.
class GameObject final : public Identifiable, public std::enable_shared_from_this<GameObject> {
public:
	GameObject(std::shared_ptr<ComponentRegistry> component_registry);

	// Tag by which the game object can be identified.
	std::string tag = "Game Object";

	// Returns the component registry.
	std::shared_ptr<ComponentRegistry> GetComponentRegistry();

	// Adds a component of type ComponentType to this object.
	template<typename ComponentType>
	std::shared_ptr<ComponentType> AddComponent() {
		std::shared_ptr<ComponentType> component = std::make_shared<ComponentType>(this->shared_from_this());
		this->component_registry.lock()->RegisterComponent<ComponentType>(this->GetID(), component);
		return component;
	}
	
	// Returns this object's component of type ComponentType.
	template<typename ComponentType>
	std::shared_ptr<ComponentType> GetComponent() {
		return this->component_registry.lock()->GetComponent<ComponentType>(this->GetID());
	}

	// Returns true if this object has component of type ComponentType.
	template<typename ComponentType>
	bool HasComponent() {
		return this->component_registry.lock()->HasComponent<ComponentType>(this->GetID());
	}

	// Unregisters all components associated with this game object.
	void Destroy();

private:
	std::weak_ptr<ComponentRegistry> component_registry;
};

