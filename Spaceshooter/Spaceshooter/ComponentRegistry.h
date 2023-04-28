// ComponentRegistry.h
// Krystof Hruby
// 2023

#pragma once

#include <stack>
#include <string>
#include <typeindex>
#include <unordered_map>
#include "CollisionManager.h"
#include "EngineException.h"
#include "StartScheduler.h"

// Type of Component subclass for component registry.
typedef std::type_index ComponentTypeID;

#ifndef GET_COMPONENT_TYPE_ID
	// Returns ComponentTypeID from a Component subclass.
	#define GET_COMPONENT_TYPE_ID(component_type) std::type_index(typeid(component_type))
#endif

// Holds data of all components in a scene.
class ComponentRegistry final : public Identifiable {
public:
	// Registers component of ComponentType to provided ObjectUUID.
	template<typename ComponentType>
	void RegisterComponent(ObjectUUID game_object_id, std::shared_ptr<ComponentType> component) {
		auto components = this->GetComponents(GET_COMPONENT_TYPE_ID(ComponentType));

		if (this->HasComponent<ComponentType>(game_object_id))
			throw EngineException((std::string)"Cannot register component. Component of type: " + typeid(ComponentType).name() + (std::string)" already registered for game object (ID): " + std::to_string(game_object_id));
		
		(*components)[game_object_id] = component;

		if (component->Startable())
			this->start_scheduler.ScheduleComponent(component);
		else
			component->started = true; // Pretend the component started if not Startable.

		if (auto component_collider = std::dynamic_pointer_cast<Component_Collider>(component))
			this->collision_manager.RegisterCollider(component_collider);
	}

	// Marks all components associated with provided ObjectUUID to be unregistered.
	void UnregisterComponents(ObjectUUID game_object_id);

	// Returns component of ComponentType associated with provided ObjectUUID.
	template<typename ComponentType>
	std::shared_ptr<ComponentType> GetComponent(ObjectUUID game_object_id) {
		auto components = this->GetComponents(GET_COMPONENT_TYPE_ID(ComponentType));

		if (!this->HasComponent<ComponentType>(game_object_id))
			throw EngineException((std::string)"Cannot get component. No component of type: " + typeid(ComponentType).name() + (std::string)" registered for game object (ID): " + std::to_string(game_object_id));

		// Cast to the specific ComponentType.
		return std::static_pointer_cast<ComponentType>((*components)[game_object_id]);
	}

	// Returns true if there is a component of ComponentType associated with provided ObjectUUID.
	template<typename ComponentType>
	bool HasComponent(ObjectUUID game_object_id) {
		auto components = this->GetComponents(GET_COMPONENT_TYPE_ID(ComponentType));
		return components->find(game_object_id) != components->end();
	}

	// Starts components scheduled to start.
	// Calls Update on all currently registered components.
	// Checks for collisions.
	void AllComponents_Update();

private:
	// Components are added dynamically - access through GetComponents; do not access directly.
	std::unordered_map<ComponentTypeID, std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>>> component_registry;

	// Holds UUIDs of component sets to be unregistered.
	std::stack<ObjectUUID> component_unregistry;

	StartScheduler start_scheduler;
	CollisionManager collision_manager;

	// Returns the hashmap of components of given type. Dynamically adds them if the specific type was not yet registered.
	std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>> GetComponents(ComponentTypeID component_type);

	// Calls Update on all provided active components.
	void Components_Update(std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>> components) const;

	// Unregisters all components marked to be unregistered.
	// Must be called between frames (after all Update methods) to avoid iteration errors.
	void UpdateRegistry();
};

