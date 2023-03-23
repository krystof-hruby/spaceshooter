// ComponentRegistry.cpp
// Krystof Hruby
// 2023

#include "ComponentRegistry.h"

void ComponentRegistry::AllComponents_Start() {
	for (auto components : this->component_registry)
		this->Components_Start(components.second);
}

void ComponentRegistry::AllComponents_Update() {
	for (auto components : this->component_registry)
		this->Components_Update(components.second);

	this->collision_manager.HandleCollisions();
}
