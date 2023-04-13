// ComponentRegistry.cpp
// Krystof Hruby
// 2023

#include "ComponentRegistry.h"

void ComponentRegistry::Components_Start(std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>> components) const {
	if (components->size() < 1)
		return;
	
	// If this component type never starts, save performance by not starting.
	if (!components->begin()->second->Startable())
		return;

	for (auto component : *components)
		if (component.second->is_active)
			component.second->Start();
}

void ComponentRegistry::Components_Update(std::shared_ptr<std::unordered_map<ObjectUUID, std::shared_ptr<Component>>> components) const {
	if (components->size() < 1)
		return;

	// If this component type never updates, save performance by not updating.
	if (!components->begin()->second->Updatable())
		return;

	for (auto component : *components)
		if (component.second->is_active)
			component.second->Update();
}

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

void ComponentRegistry::UnregisterComponents(ObjectUUID game_object_id) {
	this->component_unregistry.push(game_object_id);
}

void ComponentRegistry::UpdateRegistry() {
	// Iterate over all game objects set to have their components unregistered.
	while (!this->component_unregistry.empty()) {
		ObjectUUID game_object_id = this->component_unregistry.top();

		// Unregister every component associated with this game object UUID.
		for (auto components : this->component_registry) {
			if (components.second->find(game_object_id) == components.second->end())
				continue;

			// Remove component from collider registry (if collider).
			if (auto component_collider = std::dynamic_pointer_cast<Component_Collider>((*components.second)[game_object_id]))
				this->collision_manager.UnregisterCollider(component_collider);

			// Remove component from registry.
			components.second->erase(game_object_id);
		}
	
		this->component_unregistry.pop();
	}
}
