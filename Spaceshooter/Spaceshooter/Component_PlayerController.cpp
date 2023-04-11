// Component_PlayerController.cpp
// Krystof Hruby
// 2023

#include "Component_PlayerController.h"

#include "Component_PlayerBulletController.h"
#include "Component_PlayerInput.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Global.h"

void Component_PlayerController::Start() {

}

void Component_PlayerController::Update() {
	std::shared_ptr<Component_Transform> transform = this->game_object->GetComponent<Component_Transform>();
	std::shared_ptr<Component_PlayerInput> player_input = this->game_object->GetComponent<Component_PlayerInput>();

	// Update rotation.
	transform->rotation += this->rotation_speed * player_input->GetInput_Rotation() * Time::delta_time;

	// Set direction vector.
	Vector2D direction_vector;
	direction_vector.setBearing(transform->rotation, 1);

	// Update movement.
	transform->position += this->movement_speed * player_input->GetInput_Movement() * direction_vector * Time::delta_time;

	// Firing enabled if reloaded.
	if (player_input->GetInput_Shooting() && (this->reload_time > this->reload_speed)) {
		this->ShootBullet(transform->position, transform->rotation, direction_vector);

		// Reset reload time.
		this->reload_time = 0;
	}

	this->reload_time += Time::delta_time;
}

void Component_PlayerController::ShootBullet(Vector2D position, float rotation, Vector2D direction) {
	std::shared_ptr<GameObject> bullet = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::PlayerBullet, this->game_object->GetComponentRegistry());
	bullet->GetComponent<Component_Transform>()->position = position;
	bullet->GetComponent<Component_Transform>()->rotation = rotation;
	bullet->GetComponent<Component_PlayerBulletController>()->direction = direction;
}
