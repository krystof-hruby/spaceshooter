// Component_PlayerBulletController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_ScoreManager.h"
#include "vector2D.h"

class Component_PlayerBulletController final : public Component {
public:
	using Component::Component;
	inline bool Startable() const override { return false; }
	void Update() override;
	
	std::weak_ptr<Component_ScoreManager> score_manager;
	float movement_speed = 1;
	Vector2D movement_direction;
};

