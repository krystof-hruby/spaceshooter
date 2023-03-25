// ComponentRegistry.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include "CollisionManager.h"
#include "Component.h"
#include "EngineException.h"
#include "Identifiable.h"

// Type of Component subclass for component registry.
typedef std::type_index ComponentTypeID;

#ifndef GET_COMPONENT_TYPE_ID
	// Returns ComponentTypeID from a Component subclass.
	#define GET_COMPONENT_TYPE_ID(component_type) std::type_index(typeid(component_type))
#endif

// Holds data of all components in a scene.
class ComponentRegistry final : public Identifiable {
private:
	// Components are added dynamically - access through GetComponents; do not access directly.
	std::unordered_map<ComponentTypeID, std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>>> component_registry;

	// Returns the hashmap of components of given type. Dynamically adds them if the specific type was not yet registered.
	std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>> GetComponents(ComponentTypeID component_type);

	CollisionManager collision_manager;

	// Calls Start on all provided active components.
	template<typename ComponentType>
	void Components_Start(std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<ComponentType>>> components) {
		for (auto component : *components)
			if (component.second->is_active)
				component.second->Start();
	}

	// Calls Update on all provided active components.
	template<typename ComponentType>
	void Components_Update(std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<ComponentType>>> components) {
		// If this component type never updates, save performance by not updating.
		if (!components->begin()->second->Updatable())
			return;

		for (auto component : *components)
			if (component.second->is_active)
				component.second->Update();
	}

public:
	// Calls Start on all currently registered components.
	void AllComponents_Start();
	// Calls Update on all currently registered components.
	void AllComponents_Update();

	// Returns component of ComponentType associated with provided ObjectUUID.
	template<typename ComponentType>
	std::shared_ptr<ComponentType> GetComponent(ObjectUUID game_object_id) {
		auto components = this->GetComponents(GET_COMPONENT_TYPE_ID(ComponentType));

		if (!(*components)[game_object_id])
			throw EngineException((std::string)"Cannot get component. No component of type: " + typeid(ComponentType).name() + (std::string)" registered for game object (ID): " + std::to_string(game_object_id));

		// Cast to the specific ComponentType.
		return std::static_pointer_cast<ComponentType>((*components)[game_object_id]);
	}

	// Registers component of ComponentType to provided ObjectUUID.
	template<typename ComponentType>
	void RegisterComponent(ObjectUUID game_object_id, std::shared_ptr<ComponentType> component) {
		auto components = this->GetComponents(GET_COMPONENT_TYPE_ID(ComponentType));

		if ((*components)[game_object_id])
			throw EngineException((std::string)"Cannot register component. Component of type: " + typeid(ComponentType).name() + (std::string)" already registered for game object (ID): " + std::to_string(game_object_id));
		
		(*components)[game_object_id] = component;

		if (auto component_collider = std::dynamic_pointer_cast<Component_Collider>(component))
			this->collision_manager.RegisterCollider(component_collider);
	}

	// Unregisters component of ComponentType from provided ObjectUUID.
	template<typename ComponentType>
	void UnregisterComponent(ObjectUUID game_object_id) {
		auto components = this->GetComponents(GET_COMPONENT_TYPE_ID(ComponentType));

		if (!(*components)[game_object_id])
			throw EngineException((std::string)"Cannot unregister component. No component of type: " + typeid(ComponentType).name() + (std::string)" registered for game object (ID): " + std::to_string(game_object_id));

		if (auto component_collider = std::dynamic_pointer_cast<Component_Collider>((*components)[game_object_id]))
			this->collision_manager.UnregisterCollider(component_collider);

		components->erase(game_object_id);
	}
};

