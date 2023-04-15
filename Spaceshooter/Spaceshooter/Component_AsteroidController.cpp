// Component_AsteroidController.cpp
// Krystof Hruby
// 2023

#include "Component_AsteroidController.h"

#include "Component_Transform.h"
#include "GameObject.h"
#include "Global.h"

void Component_AsteroidController::Explode() {
	// TODO: play animation
	
	// after played:
	this->is_active = false;
}

void Component_AsteroidController::Update() {
	if (!this->is_active)
		this->GetGameObject()->Destroy();

	this->GetGameObject()->GetComponent<Component_Transform>()->position += this->movement_direction * this->movement_speed * Time::delta_time;
	this->GetGameObject()->GetComponent<Component_Transform>()->rotation += rotation_speed * rotation_direction * (float)Time::delta_time;

	// Despawn asteroid if out of bounds.
	if (!this->IsInBounds()) {
		this->GetGameObject()->Destroy();
	}
}

bool Component_AsteroidController::IsInBounds() {
	return ActiveBounds::IsInBounds(this->GetGameObject()->GetComponent<Component_Transform>()->position);
}