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