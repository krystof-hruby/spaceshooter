// ComponentRegistry.cpp
// Krystof Hruby
// 2023

#include "ComponentRegistry.h"

void ComponentRegistry::AllComponents_Start() {
	this->Components_Start(this->components_transform);
}

void ComponentRegistry::AllComponents_Update() {
	this->Components_Update(this->components_transform);
}
