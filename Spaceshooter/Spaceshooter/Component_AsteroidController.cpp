// Component_AsteroidController.cpp
// Krystof Hruby
// 2023

#include "Component_AsteroidController.h"

#include "ActiveBounds.h"
#include "Component_Animator.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "Time.h"

void Component_AsteroidController::Update() {
	this->GetGameObject()->GetComponent<Component_Transform>()->position += this->movement_direction * this->movement_speed * Time::delta_time;
	this->GetGameObject()->GetComponent<Component_Transform>()->rotation += rotation_speed * rotation_direction * (float)Time::delta_time;

	// Despawn asteroid if out of bounds or exploded.
	if (this->GetGameObject()->GetComponent<Component_Animator>()->AnimationFinished("asteroid explosion") || !this->IsInBounds()) {
		this->GetGameObject()->Destroy();
	}
}

void Component_AsteroidController::Explode() {
	// Hide sprite.
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false;
	
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("asteroid explosion");
}

bool Component_AsteroidController::IsInBounds() {
	return ActiveBounds::IsInBounds(this->GetGameObject()->GetComponent<Component_Transform>()->position);
}

