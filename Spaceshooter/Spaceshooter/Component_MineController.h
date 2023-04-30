// Component_MineController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "vector2D.h"

class Component_MineController : public Component {
public:
	using Component::Component;
	void Start();
	void Update();

	Vector2D spawn_position;

	void Explode();
};

