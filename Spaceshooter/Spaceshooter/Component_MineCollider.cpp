// Component_MineCollider.cpp
// Krystof Hruby
// 2023

#include "Component_MineCollider.h"

#include "Component_MineController.h"
#include "GameObject.h"

void Component_MineCollider::OnCollisionEnter(std::shared_ptr<GameObject> other) {
	if (other->tag == "Player" || other->tag == "Player Bullet" || other->tag == "Boss")
		this->GetGameObject()->GetComponent<Component_MineController>()->Explode();
}
