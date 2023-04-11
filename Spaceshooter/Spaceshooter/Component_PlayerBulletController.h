// Component_PlayerBulletController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "vector2D.h"

class Component_PlayerBulletController final : public Component {
public:
	using Component::Component;
	
	float speed = 5;
	Vector2D direction;

	inline bool Startable() const override { return false; }

	void Update() override;
};

