// Component_EnemyShipCollider.cpp
// Krystof Hruby
// 2023

#include "Component_EnemyShipCollider.h"

#include "Component_EnemyShipController.h"
#include "GameObject.h"

void Component_EnemyShipCollider::OnCollisionEnter(std::shared_ptr<GameObject> other) {
	if (other->tag == "Player" || other->tag == "Player Bullet" || other->tag == "Asteroid") {
		this->GetGameObject()->GetComponent<Component_EnemyShipController>()->Explode();
		this->is_active = false; // Disable further collision.
	}
}
