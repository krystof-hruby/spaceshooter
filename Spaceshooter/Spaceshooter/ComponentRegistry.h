// ComponentRegistry.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>
#include <unordered_map>

#include "Identifiable.h"

#include "Component.h"
#include "Component_Transform.h"

// Holds data of all components in a scene.
class ComponentRegistry : public Identifiable {
private:
	std::unordered_map<UUID, std::shared_ptr<Component_Transform>> components_transform;


	template<typename ComponentType>
	void Components_Start(std::unordered_map<UUID, std::shared_ptr<ComponentType>> components) {
		for (auto component : components) {
			component.second->Start();
		}
	}
	
	template<typename ComponentType>
	void Components_Update(std::unordered_map<UUID, std::shared_ptr<ComponentType>> components) {
		for (auto component : components) {
			component.second->Update();
		}
	}

public:
	void AllComponents_Start();
	void AllComponents_Update();
	
	// COMPONENTS:

	template<typename ComponentType>
	std::shared_ptr<ComponentType> GetComponent(UUID game_object_id);
	
	template<typename ComponentType>
	void AddComponent(UUID game_object_id, std::shared_ptr<ComponentType> component);

	template<typename ComponentType>
	void RemoveComponent(UUID game_object_id);

	// Transform:

	template<>
	std::shared_ptr<Component_Transform> GetComponent<Component_Transform>(UUID game_object_id) {
		return this->components_transform[game_object_id];
	}

	template<>
	void AddComponent<Component_Transform>(UUID game_object_id, std::shared_ptr<Component_Transform> component) {
		this->components_transform.insert({ game_object_id, component });
	}

	template<>
	void RemoveComponent<Component_Transform>(UUID game_object_id) {
		this->components_transform.erase(game_object_id);
	}

	// 
};

