// Component_EnemyShipController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"

class Component_EnemyShipController final : public Component {
private:
	bool IsInBounds();

public:
	using Component::Component;

	float movement_speed = 1;
	// Weak pointer to avoid cyclical references.
	std::weak_ptr<GameObject> player;

	void Explode();
	void Update() override;
};

