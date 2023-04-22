// Component_PlayerCollider.cpp
// Krystof Hruby
// 2023

#include "Component_PlayerCollider.h"
#include "GameObject.h"

void Component_PlayerCollider::OnCollisionEnter(std::shared_ptr<GameObject> other) {
	if (other->tag == "Asteroid") {
		
	}
}
