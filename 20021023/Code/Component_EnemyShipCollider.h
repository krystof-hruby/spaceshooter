// Component_EnemyShipCollider.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_CircleCollider.h"

class Component_EnemyShipCollider final : public Component_CircleCollider {
public:
	using Component_CircleCollider::Component_CircleCollider;

protected:
	void OnCollisionEnter(std::shared_ptr<GameObject> other) override;
};

