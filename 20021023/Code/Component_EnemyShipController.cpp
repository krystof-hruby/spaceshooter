// Component_EnemyShipController.cpp
// Krystof Hruby
// 2023

#include "Component_EnemyShipController.h"

#include "ActiveBounds.h"
#include "AudioClips.h"
#include "Component_Animator.h"
#include "Component_EnemyShipCollider.h"
#include "GameObject.h"
#include "Time.h"

void Component_EnemyShipController::Update() {
	auto transform = this->GetGameObject()->GetComponent<Component_Transform>();
	auto animator = this->GetGameObject()->GetComponent<Component_Animator>();

	// Despawn asteroid if out of bounds or exploded.
	if (animator->AnimationFinished("enemy ship explosion") || !ActiveBounds::IsInBounds(transform->position)) {
		this->GetGameObject()->Destroy();
	}
	
	if (this->player_transform.expired())
		return; // Player was destroyed.
	
	auto player_transform = this->player_transform.lock();

	// Interpolate between this position and player position.
	float time_step = (float)Time::delta_time * this->movement_speed;
	transform->position.XValue = (1 - time_step) * transform->position.XValue + time_step * player_transform->position.XValue;
	transform->position.YValue = (1 - time_step) * transform->position.YValue + time_step * player_transform->position.YValue;
}

void Component_EnemyShipController::Explode() {
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false; // Hide sprite.
	this->GetGameObject()->GetComponent<Component_EnemyShipCollider>()->is_active = false; // Disable collision.
	this->GetGameObject()->GetComponent<Component_Transform>()->scale = 0.25f;
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("enemy ship explosion");
	AudioPlayer::GetInstance().PlayAudioClip(AUDIO_ENEMY_SHIP_EXPLOSION, 75);
}
