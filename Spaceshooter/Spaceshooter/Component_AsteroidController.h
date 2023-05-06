// Component_AsteroidController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_Level1Manager.h"
#include "vector2D.h"

const int CLOCKWISE = 1;
const int COUNTERCLOCKWISE = -1;

class Component_AsteroidController final : public Component {
public:
	using Component::Component;
	inline bool Startable() const override { return false; }
	void Update() override;

	float movement_speed = 1;
	Vector2D movement_direction;
	float rotation_speed = 1;
	int rotation_direction = CLOCKWISE;

	void Explode();
};

