// GameObject.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>

#include "Identifiable.h"
#include "ComponentRegistry.h"

class GameObject : public Identifiable {
private:
	std::shared_ptr<ComponentRegistry> component_registry;

public:
	GameObject(std::shared_ptr<ComponentRegistry> component_registry);

	template<typename ComponentType>
	std::shared_ptr<ComponentType> GetComponent() {
		return this->component_registry->GetComponent<ComponentType>(this->GetID());
	}

	template<typename ComponentType>
	void AddComponent(std::shared_ptr<ComponentType> component) {
		return this->component_registry->AddComponent<ComponentType>(this->GetID(), component);
	}

	template<typename ComponentType>
	void RemoveComponent() {
		return this->component_registry->RemoveComponent<ComponentType>(this->GetID());
	}
};

