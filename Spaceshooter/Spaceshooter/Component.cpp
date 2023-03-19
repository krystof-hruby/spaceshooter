// Component.cpp
// Krystof Hruby
// 2023

#include "Component.h"

Component::Component(std::shared_ptr<GameObject> game_object) {
	this->game_object = game_object;
}

// Returns the game object with this component.
std::shared_ptr<GameObject> Component::GetGameObject() {
	return this->game_object;
}

// Called once at the start of a level.
void Component::Start() { }

// Called once every frame.
void Component::Update() { }