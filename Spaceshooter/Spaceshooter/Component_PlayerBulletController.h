// Component_PlayerBulletController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "vector2D.h"

// Controls a player bullet.
class Component_PlayerBulletController final : public Component {
public:
	using Component::Component;
	inline bool Startable() const override { return false; }
	void Update() override;
	
	float movement_speed = 1;
	Vector2D movement_direction;
};

