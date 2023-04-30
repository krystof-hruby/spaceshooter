// Component_MineCollider.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_CircleCollider.h"

class Component_MineCollider : public Component_CircleCollider {
public:
	using Component_CircleCollider::Component_CircleCollider;

	void OnCollisionEnter(std::shared_ptr<GameObject> other) override;
};

