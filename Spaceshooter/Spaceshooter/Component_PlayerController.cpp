// Component_PlayerController.cpp
// Krystof Hruby
// 2023

#include "Component_PlayerController.h"

#include "Component_Animator.h"
#include "Component_PlayerBulletController.h"
#include "Component_PlayerCollider.h"
#include "Component_PlayerInput.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Global.h"

void Component_PlayerController::Start() {
	
}

void Component_PlayerController::Update() {
	if (this->exploded) {
		if (this->GetGameObject()->GetComponent<Component_Animator>()->AnimationFinished("player explode"))
			this->GetGameObject()->Destroy();

		// TODO: display end screen

		return;
	}

	std::shared_ptr<Component_Transform> transform = this->GetGameObject()->GetComponent<Component_Transform>();
	std::shared_ptr<Component_PlayerInput> player_input = this->GetGameObject()->GetComponent<Component_PlayerInput>();

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
		this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/spaceships/spaceship_green_right.bmp");
	else if (player_input->GetInput_Rotation() < 0)
		this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/spaceships/spaceship_green_left.bmp");
	else // No rotation.
		this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/spaceships/spaceship_green.bmp");
}


void Component_PlayerController::Explode() {
	this->exploded = true;
	
	// Hide sprite.
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false;
	// Disable collision.
	this->GetGameObject()->GetComponent<Component_PlayerCollider>()->is_active = false;

	this->GetGameObject()->GetComponent<Component_Animator>()->StopAnimation();
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("player explode");
}

inline bool Component_PlayerController::Reloaded() const {
	return this->reload_time > this->reload_period;
}

void Component_PlayerController::ShootBullet(Vector2D position, float rotation, Vector2D direction) {
	std::shared_ptr<GameObject> bullet = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::PlayerBullet, this->GetGameObject()->GetComponentRegistry());
	bullet->GetComponent<Component_Transform>()->position = position;
	bullet->GetComponent<Component_Transform>()->rotation = rotation;
	bullet->GetComponent<Component_PlayerBulletController>()->movement_direction = direction;
	bullet->GetComponent<Component_PlayerBulletController>()->score_manager = this->score_manager;

	// Hold reference to bullet, otherwise loses pointer and gets deallocated.
	this->bullets.push_back(bullet);
}
