// Component_PlayerController.h
// Krystof Hruby
// 2023

#pragma once

#include <vector>

#include "Component.h"
#include "Component_ScoreManager.h"
#include "vector2D.h"

class Component_PlayerController final : public Component {
private:
	float reload_time = 0;

	inline bool Reloaded() const { return this->reload_time > this->reload_period; }
	void ShootBullet(Vector2D position, float rotation, Vector2D direction);

public:
	using Component::Component;

	std::weak_ptr<Component_ScoreManager> score_manager;
	Vector2D canon_offset;
	float movement_speed = 1;
	float rotation_speed = 1;
	float reload_period = 1;

	void Explode();
	void Start() override;
	void Update() override;
};

