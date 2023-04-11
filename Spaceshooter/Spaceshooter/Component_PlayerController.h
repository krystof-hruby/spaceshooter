// Component_PlayerController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "vector2D.h"

class Component_PlayerController final : public Component {
private:
	float reload_time = 0;

public:
	using Component::Component;

	float movement_speed = 500;
	float rotation_speed = 5;
	float reload_speed = 1;

	void Start() override;
	void Update() override;
	void ShootBullet(Vector2D position, float rotation, Vector2D direction);
};

