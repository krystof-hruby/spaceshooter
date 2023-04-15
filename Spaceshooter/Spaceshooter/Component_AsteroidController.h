// Component_AsteroidController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "vector2D.h"

#define CLOCKWISE 1
#define COUNTERCLOCKWISE -1

class Component_AsteroidController final : public Component {
public:
	using Component::Component;

	float movement_speed = 1;
	Vector2D movement_direction;
	float rotation_speed = 1;
	int rotation_direction = CLOCKWISE;

	bool IsInBounds();
	void Explode();
	void Update() override;
};

