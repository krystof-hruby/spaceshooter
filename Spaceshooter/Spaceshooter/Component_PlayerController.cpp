// Component_PlayerController.cpp
// Krystof Hruby
// 2023

#include "Component_PlayerController.h"

#include "ActiveBounds.h"
#include "AudioClips.h"
#include "Component_Animator.h"
#include "Component_AudioEmitter.h"
#include "Component_PlayerBulletController.h"
#include "Component_PlayerCollider.h"
#include "Component_PlayerInput.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Scene_Level2.h"
#include "SceneManager.h"
#include "Sprites.h"
#include "Time.h"

void Component_PlayerController::Start() {
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false;

	this->current_state = this->state_grace_period;
}

void Component_PlayerController::Update() {
	this->current_state->Play(this->shared_from_this());

	if (!ActiveBounds::IsInBounds(this->GetGameObject()->GetComponent<Component_Transform>()->position))
		this->GetGameObject()->Destroy();
}

void Component_PlayerController::ChangeState(std::shared_ptr<PlayerState> player_state) {
	this->current_state = player_state;
}

void Component_PlayerController::Explode() {
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false; // Hide sprite.
	this->GetGameObject()->GetComponent<Component_PlayerCollider>()->is_active = false; // Disable collision.
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("player explode");
	this->GetGameObject()->GetComponent<Component_AudioEmitter>()->Play(AUDIO_PLAYER_EXPLOSION);
	this->current_state = this->state_exploding;
}

void Component_PlayerController::Despawn() {
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false; // Hide sprite.
	this->GetGameObject()->GetComponent<Component_PlayerCollider>()->is_active = false; // Disable collision.
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("player despawn");
	this->GetGameObject()->GetComponent<Component_AudioEmitter>()->Play(AUDIO_PLAYER_SPAWN);
	this->current_state = this->state_despawning;
}

void Component_PlayerController::ShootBullet(Vector2D position, float rotation, Vector2D direction) {
	std::shared_ptr<GameObject> bullet = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::PlayerBullet, this->GetGameObject()->GetComponentRegistry());
	bullet->GetComponent<Component_Transform>()->position = position;
	bullet->GetComponent<Component_Transform>()->rotation = rotation;
	bullet->GetComponent<Component_PlayerBulletController>()->movement_direction = direction;
	bullet->GetComponent<Component_PlayerBulletController>()->score_manager = this->score_manager;

	Scene::Instantiate(bullet);

	this->GetGameObject()->GetComponent<Component_AudioEmitter>()->Play(AUDIO_PLAYER_PROJECTILE);
}
