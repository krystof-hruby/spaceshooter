// ComponentRegistry.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <stack>

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

struct ObjectUUIDtoComponentTypeID {
	ObjectUUID object_uuid;
	ComponentTypeID component_type_id;
};

// Holds data of all components in a scene.
class ComponentRegistry final : public Identifiable {
private:
	// Components are added dynamically - access through GetComponents; do not access directly.
	std::unordered_map<ComponentTypeID, std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>>> component_registry;

	CollisionManager collision_manager;
	
	// Holds info about components marked to be unregistered.
	std::stack<ObjectUUIDtoComponentTypeID> component_unregistry;

	// Holds UUIDs of component sets to be unregistered.
	std::stack<ObjectUUID> game_object_unregistry;

	// Returns the hashmap of components of given type. Dynamically adds them if the specific type was not yet registered.
	std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>> GetComponents(ComponentTypeID component_type);

	// Calls Start on all provided active components.
	template<typename ComponentType>
	void Components_Start(std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<ComponentType>>> components) const  {
		// If this component type never starts, save performance by not starting.
		if (!components->begin()->second->Startable())
			return;

		for (auto component : *components)
			if (component.second->is_active)
				component.second->Start();
	}

	// Calls Update on all provided active components.
	template<typename ComponentType>
	void Components_Update(std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<ComponentType>>> components) const {
		// If this component type never updates, save performance by not updating.
		if (!components->begin()->second->Updatable())
			return;

		for (auto component : *components)
			if (component.second->is_active)
				component.second->Update();
	}

	// Unregisters component of ComponentTypeID from provided ObjectUUID.
	void UnregisterComponent(ObjectUUID game_object_id, ComponentTypeID component_type_id) {
		auto components = this->GetComponents(component_type_id);

		if (!(*components)[game_object_id])
			throw EngineException((std::string)"Cannot unregister component. No component of type: " + component_type_id.name() + (std::string)" registered for game object (ID): " + std::to_string(game_object_id));

		if (auto component_collider = std::dynamic_pointer_cast<Component_Collider>((*components)[game_object_id]))
			this->collision_manager.UnregisterCollider(component_collider);

		components->erase(game_object_id);
	}

	// Unregisters all components of game object with provided ObjectUUID.
	void UnregisterGameObject(ObjectUUID game_object_id);

public:
	// Calls Start on all currently registered components.
	void AllComponents_Start() const;
	// Calls Update on all currently registered components.
	void AllComponents_Update() const;

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

	// Marks component of ComponentType of provided ObjectUUID to be unregistered.
	template<typename ComponentType>
	void UnregisterComponent(ObjectUUID game_object_id) {
		ObjectUUIDtoComponentTypeID component = { game_object_id, GET_COMPONENT_TYPE_ID(ComponentType) };
		this->component_unregistry.push(component);
	}

	// Marks all components associated with provided ObjectUUID to be unregistered.
	void UnregisterAllComponents(ObjectUUID game_object_id);

	// Unregisters all components marked to be unregistered.
	// Must be called between frames (after all Update methods) to avoid iteration errors.
	void ClearRegistry();
};

