// Component_EnemyShipController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_Transform.h"

class Component_EnemyShipController final : public Component {
public:
	using Component::Component;

	float movement_speed = 1;
	std::weak_ptr<Component_Transform> player_transform;

	void Explode();
	inline bool Startable() const override { return false; }
	void Update() override;
};

