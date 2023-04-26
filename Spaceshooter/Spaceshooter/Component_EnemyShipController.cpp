// Component_EnemyShipController.cpp
// Krystof Hruby
// 2023

#include "Component_EnemyShipController.h"

#include "ActiveBounds.h"
#include "Component_Animator.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "Time.h"

void Component_EnemyShipController::Update() {
	// Despawn asteroid if out of bounds or exploded.
	if (this->GetGameObject()->GetComponent<Component_Animator>()->AnimationFinished("enemy ship explosion") || !this->IsInBounds()) {
		this->GetGameObject()->Destroy();
	}
	
	if (!this->player.lock() || !this->player.lock()->HasComponent<Component_Transform>())
		return; // Player was destroyed.
	
	std::shared_ptr<Component_Transform> transform = this->GetGameObject()->GetComponent<Component_Transform>();
	std::shared_ptr<Component_Transform> player_transform = this->player.lock()->GetComponent<Component_Transform>();

	// Interpolate between this position and player position.
	float time_step = (float)Time::delta_time * this->movement_speed;
	Vector2D new_position;
	new_position.XValue = (1 - time_step) * transform->position.XValue + time_step * player_transform->position.XValue;
	new_position.YValue = (1 - time_step) * transform->position.YValue + time_step * player_transform->position.YValue;
	transform->position = new_position;
}

bool Component_EnemyShipController::IsInBounds() {
	return ActiveBounds::IsInBounds(this->GetGameObject()->GetComponent<Component_Transform>()->position);
}

void Component_EnemyShipController::Explode() {
	// Hide sprite.
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false;

	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("enemy ship explosion");
}
