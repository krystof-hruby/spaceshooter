// Component_PlayerCollider.cpp
// Krystof Hruby
// 2023

#include "Component_PlayerCollider.h"

#include "Component_PlayerController.h"
#include "GameObject.h"
#include "Debugging.h"

void Component_PlayerCollider::OnCollisionEnter(std::shared_ptr<GameObject> other) {
	#if PLAYER_INVINCIBILITY
		return;
	#endif
	
	if (other->tag == "Asteroid" || other->tag == "Enemy Ship" || other->tag == "Boss" || other->tag == "Homing Missile" || other->tag == "Laser" || other->tag == "Mine")
		this->GetGameObject()->GetComponent<Component_PlayerController>()->Explode();
}
