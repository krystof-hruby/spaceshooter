// Component.cpp
// Krystof Hruby
// 2023

#include "Component.h"

Component::Component(std::shared_ptr<GameObject> game_object) {
	this->game_object = game_object;
}

std::shared_ptr<GameObject> Component::GetGameObject() {
	return this->game_object.lock();
}

void Component::Start() { }

void Component::Update() { }