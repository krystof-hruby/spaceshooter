// ComponentRegistry.cpp
// Krystof Hruby
// 2023

#include "ComponentRegistry.h"

// Calls starts on all currently registered components.
void ComponentRegistry::AllComponents_Start() {
	this->Components_Start(this->components_transform);
}

// Calls update on all currently registered components.
void ComponentRegistry::AllComponents_Update() {
	this->Components_Update(this->components_transform);
}
