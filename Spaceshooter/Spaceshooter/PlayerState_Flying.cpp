// PlayerState_Flying.cpp
// Krystof Hruby
// 2023

#include "PlayerState_Flying.h"

#include "Component_PlayerInput.h"
#include "Component_PlayerController.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Time.h"

void PlayerState_Flying::Play(std::shared_ptr<Component_PlayerController> player_controller) {
	auto transform = player_controller->GetGameObject()->GetComponent<Component_Transform>();
	auto sprite_renderer = player_controller->GetGameObject()->GetComponent<Component_SpriteRenderer>();
	auto player_input = player_controller->GetGameObject()->GetComponent<Component_PlayerInput>();

	// Update rotation.
	transform->rotation += player_controller->rotation_speed * player_input->GetInput_Rotation() * (float)Time::delta_time;

	// Set direction vector.
	Vector2D direction_vector;
	direction_vector.setBearing(transform->rotation, 1);

	// Update movement.
	transform->position += player_controller->movement_speed * player_input->GetInput_Movement() * direction_vector * (float)Time::delta_time;

	// Update sprite.
	if (player_input->GetInput_Rotation() > 0)
		sprite_renderer->SetSprite(SPRITE_SPACESHIP_GREEN_RIGHT);
	else if (player_input->GetInput_Rotation() < 0)
		sprite_renderer->SetSprite(SPRITE_SPACESHIP_GREEN_LEFT);
	else // No rotation.
		sprite_renderer->SetSprite(SPRITE_SPACESHIP_GREEN);

	// Firing enabled if reloaded.
	if (player_input->GetInput_Shooting() && this->reload_time > player_controller->reload_period) {
		player_controller->ShootBullet(transform->position, transform->rotation, direction_vector);

		// Reset reload time.
		this->reload_time = 0;
	}
	this->reload_time += (float)Time::delta_time;

	if (player_controller->score_manager.lock()->ReachedGoal())
		this->free_roaming_time += (float)Time::delta_time;

	if (this->free_roaming_time > player_controller->free_roaming_period)
		player_controller->Despawn();
}
