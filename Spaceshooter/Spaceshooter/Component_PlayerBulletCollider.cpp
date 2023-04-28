// Component_PlayerBulletCollider.cpp
// Krystof Hruby
// 2023

#include "Component_PlayerBulletCollider.h"

#include "Component_PlayerBulletController.h"
#include "GameObject.h"

void Component_PlayerBulletCollider::OnCollisionEnter(std::shared_ptr<GameObject> other) {
	if (other->tag == "Asteroid" || other->tag == "Enemy Ship" || other->tag == "Boss" || other->tag == "Homing Missile" || other->tag == "Laser") {
		this->GetGameObject()->GetComponent<Component_PlayerBulletController>()->score_manager.lock()->score += 1;
		this->GetGameObject()->Destroy();
	}
}
