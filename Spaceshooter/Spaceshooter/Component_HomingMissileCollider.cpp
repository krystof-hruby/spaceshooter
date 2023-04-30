// Component_HomingMissileCollider.cpp
// Krystof Hruby
// 2023

#include "Component_HomingMissileCollider.h"

#include "Component_HomingMissileController.h"
#include "GameObject.h"

void Component_HomingMissileCollider::OnCollisionEnter(std::shared_ptr<GameObject> other) {
	if (other->tag == "Player" || other->tag == "Homing Missile" || other->tag == "Player Bullet")
		this->GetGameObject()->GetComponent<Component_HomingMissileController>()->Explode();
}
