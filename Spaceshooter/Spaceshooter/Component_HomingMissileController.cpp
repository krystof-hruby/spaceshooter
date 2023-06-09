// Component_HomingMissileController.cpp
// Krystof Hruby
// 2023

#include "Component_HomingMissileController.h"

#include "ActiveBounds.h"
#include "AudioClips.h"
#include "Component_Animator.h"
#include "Component_HomingMissileCollider.h"
#include "GameObject.h"
#include "Time.h"

void Component_HomingMissileController::Start() {
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false; // Hide sprite.
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("homing missile spawn");
	this->initial_position = this->GetGameObject()->GetComponent<Component_Transform>()->position;
}

void Component_HomingMissileController::Update() {
	auto transform = this->GetGameObject()->GetComponent<Component_Transform>();
	auto sprite_renderer = this->GetGameObject()->GetComponent<Component_SpriteRenderer>();
	auto animator = this->GetGameObject()->GetComponent<Component_Animator>();

	// Despawn asteroid if out of bounds or exploded.
	if (animator->AnimationFinished("homing missile explosion") || !ActiveBounds::IsInBounds(transform->position)) {
		this->GetGameObject()->Destroy();
		return;
	}

	if (!animator->AnimationFinished("homing missile spawn") || this->exploded)
		return;
	
	sprite_renderer->is_active = true;
	transform->rotation += (float)Time::delta_time;

	if (this->player_transform.expired())
		return; // Player was destroyed.

	auto player_transform = this->player_transform.lock();

	// Interpolate between this position and player position.
	float time_step = (float)Time::delta_time * this->movement_speed;
	transform->position.XValue = (1 - time_step) * transform->position.XValue + time_step * player_transform->position.XValue;
	transform->position.YValue = (1 - time_step) * transform->position.YValue + time_step * player_transform->position.YValue;
}

void Component_HomingMissileController::Explode() {
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false; // Hide sprite.
	this->GetGameObject()->GetComponent<Component_HomingMissileCollider>()->is_active = false; // Disable collision.
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("homing missile explosion");
	AudioPlayer::GetInstance().PlayAudioClip(AUDIO_HOMING_MISSILE_EXPLOSION, 80);
	this->exploded = true;
}
