// ComponentRegistry.cpp
// Krystof Hruby
// 2023

#include "ComponentRegistry.h"

void ComponentRegistry::AllComponents_Start() const {
	for (auto components : this->component_registry)
		this->Components_Start(components.second);
}

void ComponentRegistry::AllComponents_Update() const {
	for (auto components : this->component_registry)
		this->Components_Update(components.second);

	this->collision_manager.HandleCollisions();
}

std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>> ComponentRegistry::GetComponents(ComponentTypeID component_type) {
	// If no components of that type registered, dynamically add storage for them first.
	if (!this->component_registry[component_type])
		this->component_registry[component_type] = std::make_shared<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>>();

	return this->component_registry[component_type];
}

void ComponentRegistry::UnregisterAllComponents(ObjectUUID game_object_id) {
	this->game_object_unregistry.push(game_object_id);
}

void ComponentRegistry::UnregisterGameObject(ObjectUUID game_object_id) {
	for (auto components : this->component_registry) {
		if (!(*components.second)[game_object_id])
			continue;

		// Remove comonent from registry.
		if (auto component_collider = std::dynamic_pointer_cast<Component_Collider>((*components.second)[game_object_id]))
			this->collision_manager.UnregisterCollider(component_collider);

		components.second->erase(game_object_id);
	}
}

void ComponentRegistry::ClearRegistry() {
	// Unregister singular components.
	while (!this->component_unregistry.empty()) {
		ObjectUUIDtoComponentTypeID component = this->component_unregistry.top();
		this->UnregisterComponent(component.object_uuid, component.component_type_id);
		this->component_unregistry.pop();
	}

	// Unregister component sets.
	while (!this->game_object_unregistry.empty()) {
		this->UnregisterGameObject(this->game_object_unregistry.top());
		this->game_object_unregistry.pop();
	}
}