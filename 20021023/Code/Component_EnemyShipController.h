// Component_EnemyShipController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_Transform.h"

// Controls an enemy ship.
class Component_EnemyShipController final : public Component {
public:
	using Component::Component;
	inline bool Startable() const override { return false; }
	void Update() override;

	std::weak_ptr<Component_Transform> player_transform;
	float movement_speed = 1;

	void Explode();
};

