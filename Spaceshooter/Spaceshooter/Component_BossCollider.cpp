// Component_BossCollider.h
// Krystof Hruby
// 2023

#include "Component_BossCollider.h"

#include "Component_BossController.h"
#include "GameObject.h"

void Component_BossCollider::OnCollisionEnter(std::shared_ptr<GameObject> other) {
	if (other->tag == "Player Bullet") {
		this->GetGameObject()->GetComponent<Component_BossController>()->GetDamaged(1);
	}
}