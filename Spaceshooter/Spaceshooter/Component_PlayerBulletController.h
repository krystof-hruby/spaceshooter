// Component_PlayerBulletController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "vector2D.h"

class Component_PlayerBulletController final : public Component {
private:
	bool IsInBounds();

public:
	using Component::Component;
	
	float movement_speed = 1;
	Vector2D movement_direction;

	inline bool Startable() const override { return false; }

	void Update() override;
};

