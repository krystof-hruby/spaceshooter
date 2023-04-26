// Component_PlayerBulletController.cpp
// Krystof Hruby
// 2023

#include "Component_PlayerBulletController.h"

#include "ActiveBounds.h"
#include "Component_Transform.h"
#include "Component_SpriteRenderer.h"
#include "GameObject.h"
#include "Time.h"

void Component_PlayerBulletController::Update() {
	this->GetGameObject()->GetComponent<Component_Transform>()->position += this->movement_direction * this->movement_speed * Time::delta_time;

	// Despawn bullet if out of bounds.
	if (!this->IsInBounds()) {
		this->GetGameObject()->Destroy();
	}
}

bool Component_PlayerBulletController::IsInBounds() {
	return ActiveBounds::IsInBounds(this->GetGameObject()->GetComponent<Component_Transform>()->position);
}