// ComponentRegistry.cpp
// Krystof Hruby
// 2023

#include "ComponentRegistry.h"
#include "Logging.h"

void ComponentRegistry::AllComponents_Start() {
	this->Components_Start(this->components_transform);
	this->Components_Start(this->components_sprite_renderer);
	this->Components_Start(this->components_input_reader);
	this->Components_Start(this->components_sound_emitter);
}

void ComponentRegistry::AllComponents_Update() {
	this->Components_Update(this->components_transform);
	this->Components_Update(this->components_sprite_renderer);
	this->Components_Update(this->components_input_reader);
	this->Components_Update(this->components_sound_emitter);
}
