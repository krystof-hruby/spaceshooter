// ComponentRegistry.h
// Krystof Hruby
// 2023

#pragma once

#include <exception>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include "Identifiable.h"
// Components:
#include "Component.h"
#include "Component_Transform.h"
#include "Component_SpriteRenderer.h"
#include "Component_InputReader.h"
#include "Component_AudioEmitter.h"

// Type of Component subclass for component registry.
typedef std::type_index ComponentTypeID;

#ifndef GET_COMPONENT_TYPE_ID
	// Returns ComponentTypeID from a Component subclass.
	#define GET_COMPONENT_TYPE_ID(component_type) std::type_index(typeid(component_type))
#endif

// Holds data of all components in a scene.
class ComponentRegistry : public Identifiable {
private:
	// Must hold all components. Otherwise will break very badly.
	std::unordered_map<ComponentTypeID, std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>>> component_registry = {
		{ GET_COMPONENT_TYPE_ID(Component_Transform), std::make_shared<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>>() },
		{ GET_COMPONENT_TYPE_ID(Component_SpriteRenderer), std::make_shared<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>>() },
		{ GET_COMPONENT_TYPE_ID(Component_InputReader), std::make_shared<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>>() },
		{ GET_COMPONENT_TYPE_ID(Component_AudioEmitter), std::make_shared<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>>() },
	};

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
		auto components = (this->component_registry[GET_COMPONENT_TYPE_ID(ComponentType)]);

		if (components->find(game_object_id) == components->end())
			throw std::exception();

		return std::static_pointer_cast<ComponentType>((*components)[game_object_id]);
	}

	// Registers component of ComponentType to provided ObjectUUID.
	template<typename ComponentType>
	void RegisterComponent(ObjectUUID game_object_id, std::shared_ptr<ComponentType> component) {
		auto components = (this->component_registry[GET_COMPONENT_TYPE_ID(ComponentType)]);
		
		if (components->find(game_object_id) != components->end())
			throw std::exception();
		
		(*components)[game_object_id] = component;
	}

	// Unregisters component of ComponentType from provided ObjectUUID.
	template<typename ComponentType>
	void UnregisterComponent(ObjectUUID game_object_id) {
		auto components = (this->component_registry[GET_COMPONENT_TYPE_ID(ComponentType)]);
		
		if (components->find(game_object_id) == components->end())
			throw std::exception();
		
		components->erase(game_object_id);
	}
};

