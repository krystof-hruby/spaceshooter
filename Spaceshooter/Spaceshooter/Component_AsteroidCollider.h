// Component_AsteroidCollider.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_CircleCollider.h"

class Component_AsteroidCollider : public Component_CircleCollider {
protected:
	void OnCollisionEnter(std::shared_ptr<GameObject> other) override;
	void OnCollisionStay(std::shared_ptr<GameObject> other) override;
	void OnCollisionLeave(std::shared_ptr<GameObject> other) override;

public:
	using Component_CircleCollider::Component_CircleCollider;
};

