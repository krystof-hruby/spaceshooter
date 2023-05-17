// Component_HomingMissileCollider.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_CircleCollider.h"

class Component_HomingMissileCollider : public Component_CircleCollider {
public:
	using Component_CircleCollider::Component_CircleCollider;

protected:
	void OnCollisionEnter(std::shared_ptr<GameObject> other) override;
};

