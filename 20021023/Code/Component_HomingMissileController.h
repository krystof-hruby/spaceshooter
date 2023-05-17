// Component_HomingMissileController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_Transform.h"

// Controls a homing missile.
class Component_HomingMissileController final : public Component {
public:
	using Component::Component;
	void Start() override;
	void Update() override;

	std::weak_ptr<Component_Transform> player_transform;
	float movement_speed = 1;

	void Explode();

private:
	Vector2D initial_position;
	bool exploded = false;
};

