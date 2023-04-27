// Component_HomingMissileController.cpp
// Krystof Hruby
// 2023

#include "Component_HomingMissileController.h"

#include "ActiveBounds.h"
#include "Component_Animator.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "Time.h"

void Component_HomingMissileController::Update() {
	auto transform = this->GetGameObject()->GetComponent<Component_Transform>();
	auto animator = this->GetGameObject()->GetComponent<Component_Animator>();

	// Despawn asteroid if out of bounds or exploded.
	if (animator->AnimationFinished("homing missile explosion") || !ActiveBounds::IsInBounds(transform->position)) {
		this->GetGameObject()->Destroy();
	}

	if (this->player_transform.expired())
		return; // Player was destroyed.

	auto player_transform = this->player_transform.lock();

	// Interpolate between this position and player position.
	float time_step = (float)Time::delta_time * (this->movement_speed + (float)Time::delta_time / 10);
	Vector2D new_position;
	new_position.XValue = (1 - time_step) * transform->position.XValue + time_step * player_transform->position.XValue;
	new_position.YValue = (1 - time_step) * transform->position.YValue + time_step * player_transform->position.YValue;
	transform->position = new_position;
}

void Component_HomingMissileController::Explode() {
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false; // Hide sprite.
	//this->GetGameObject()->GetComponent<>()->is_active = false; // Disable collision.
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("homing missile explosion");
}