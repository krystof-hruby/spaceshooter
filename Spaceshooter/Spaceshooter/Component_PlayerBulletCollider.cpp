// Component_PlayerBulletCollider.cpp
// Krystof Hruby
// 2023

#include "Component_PlayerBulletCollider.h"
#include "Component_PlayerBulletController.h"
#include "GameObject.h"

void Component_PlayerBulletCollider::OnCollisionEnter(std::shared_ptr<GameObject> other) {
	if (other->tag == "Asteroid" || other->tag == "Enemy Ship") {
		this->GetGameObject()->GetComponent<Component_PlayerBulletController>()->score_manager->score += 1;
		this->GetGameObject()->Destroy();
		this->is_active = false; // Disable further collision.
	}
}
