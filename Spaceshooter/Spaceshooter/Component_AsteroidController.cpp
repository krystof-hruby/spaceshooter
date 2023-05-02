// Component_AsteroidController.cpp
// Krystof Hruby
// 2023

#include "Component_AsteroidController.h"

#include "ActiveBounds.h"
#include "AudioClips.h"
#include "Component_Animator.h"
#include "Component_AudioEmitter.h"
#include "Component_AsteroidCollider.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "Time.h"

void Component_AsteroidController::Update() {
	auto transform = this->GetGameObject()->GetComponent<Component_Transform>();
	auto animator = this->GetGameObject()->GetComponent<Component_Animator>();

	transform->position += this->movement_direction * this->movement_speed * (float)Time::delta_time;
	transform->rotation += rotation_speed * rotation_direction * (float)Time::delta_time;

	// Despawn asteroid if out of bounds or exploded.
	if (animator->AnimationFinished("asteroid explosion") || !ActiveBounds::IsInBounds(transform->position))
		this->GetGameObject()->Destroy();
}

void Component_AsteroidController::Explode() {
	this->GetGameObject()->GetComponent<Component_AudioEmitter>()->Play(AUDIO_ASTEROID_EXPLOSION);
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false; // Hide sprite.
	this->GetGameObject()->GetComponent<Component_AsteroidCollider>()->is_active = false; // Disable collision.
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("asteroid explosion");
}

