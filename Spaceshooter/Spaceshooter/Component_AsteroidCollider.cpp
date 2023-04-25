// Component_AsteroidCollider.cpp
// Krystof Hruby
// 2023

#include "Component_AsteroidCollider.h"
#include "Component_AsteroidController.h"
#include "GameObject.h"

void Component_AsteroidCollider::OnCollisionEnter(std::shared_ptr<GameObject> other) {
	if (other->tag == "Player" || other->tag == "Player Bullet" || other->tag == "Asteroid" || other->tag == "Enemy Ship") {
		this->GetGameObject()->GetComponent<Component_AsteroidController>()->Explode();
		this->is_active = false; // Disable further collision.
	}
}
