// Component_BossCollider.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_RectangleCollider.h"

class Component_BossCollider final : public Component_RectangleCollider {
public:
	using Component_RectangleCollider::Component_RectangleCollider;

protected:
	void OnCollisionEnter(std::shared_ptr<GameObject> other) override;
};

