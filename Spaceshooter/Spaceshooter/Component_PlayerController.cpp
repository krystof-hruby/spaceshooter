// Component_PlayerController.cpp
// Krystof Hruby
// 2023

#include "Component_PlayerController.h"

#include "ActiveBounds.h"
#include "Component_Animator.h"
#include "Component_PlayerBulletController.h"
#include "Component_PlayerCollider.h"
#include "Component_PlayerInput.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Scene.h"
#include "Time.h"

void Component_PlayerController::Start() {
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("player spawn");
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false;
	this->GetGameObject()->GetComponent<Component_Transform>()->scale = 0.3f;
}

void Component_PlayerController::Update() {
	auto transform = this->GetGameObject()->GetComponent<Component_Transform>();
	auto sprite_renderer = this->GetGameObject()->GetComponent<Component_SpriteRenderer>();
	auto player_input = this->GetGameObject()->GetComponent<Component_PlayerInput>();
	auto animator = this->GetGameObject()->GetComponent<Component_Animator>();

	if (animator->AnimationFinished("player explode") || !ActiveBounds::IsInBounds(transform->position)) {
		// Was eliminated.
		this->GetGameObject()->Destroy();

		// TODO: display end screen

		return;
	}

	if (this->dead)
		return;
	
	if (!animator->AnimationFinished("player spawn")) {
		// Did not finish spawning. Do not allow to move.
		return;
	} else {
		sprite_renderer->is_active = true;
		transform->scale = 0.2f;
	}
	
	// Update rotation.
	transform->rotation += this->rotation_speed * player_input->GetInput_Rotation() * (float)Time::delta_time;

	// Set direction vector.
	Vector2D direction_vector;
	direction_vector.setBearing(transform->rotation, 1);

	// Update movement.
	transform->position += this->movement_speed * player_input->GetInput_Movement() * direction_vector * (float)Time::delta_time;

	// Firing enabled if reloaded.
	if (player_input->GetInput_Shooting() && this->Reloaded()) {
		this->ShootBullet(transform->position, transform->rotation, direction_vector);

		// Reset reload time.
		this->reload_time = 0;
	}
	this->reload_time += (float)Time::delta_time;

	// Update sprite.
	if (player_input->GetInput_Rotation() > 0)
		sprite_renderer->SetSprite(L"assets/spaceships/spaceship_green_right.png");
	else if (player_input->GetInput_Rotation() < 0)
		sprite_renderer->SetSprite(L"assets/spaceships/spaceship_green_left.png");
	else // No rotation.
		sprite_renderer->SetSprite(L"assets/spaceships/spaceship_green.png");
}


void Component_PlayerController::Explode() {
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false; // Hide sprite.
	this->GetGameObject()->GetComponent<Component_PlayerCollider>()->is_active = false; // Disable collision.
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("player explode");
	this->dead = true;
}

void Component_PlayerController::ShootBullet(Vector2D position, float rotation, Vector2D direction) {
	std::shared_ptr<GameObject> bullet = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::PlayerBullet, this->GetGameObject()->GetComponentRegistry());
	bullet->GetComponent<Component_Transform>()->position = position;
	bullet->GetComponent<Component_Transform>()->rotation = rotation;
	bullet->GetComponent<Component_PlayerBulletController>()->movement_direction = direction;
	bullet->GetComponent<Component_PlayerBulletController>()->score_manager = this->score_manager;

	Scene::Instantiate(bullet);
}
