// Component_PlayerBulletController.cpp
// Krystof Hruby
// 2023

#include "Component_PlayerBulletController.h"

#include "ActiveBounds.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "Time.h"

#include "Logging.h"

void Component_PlayerBulletController::Update() {
	auto transform = this->GetGameObject()->GetComponent<Component_Transform>();

	transform->position += this->movement_direction * this->movement_speed * Time::delta_time;

	// Despawn bullet if out of bounds.
	if (!ActiveBounds::IsInBounds(transform->position))
		this->GetGameObject()->Destroy();
}
