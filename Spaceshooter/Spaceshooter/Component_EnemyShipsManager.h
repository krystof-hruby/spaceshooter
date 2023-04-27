// Component_EnemyShipsManager.h
// Krystof Hruby
// 2023

#pragma once

#include <vector>

#include "Component.h"
#include "Component_ScoreManager.h"
#include "Component_Transform.h"
#include "vector2D.h"

class Component_EnemyShipsManager final : public Component {
private:
	float grace_period_time = 0;
	float enemy_ship_spawn_time = 0;
	float enemy_ship_spawn_period = 1; // Is randomized.
	bool enemy_ships_despawned = false;
	std::vector<std::weak_ptr<GameObject>> enemy_ships;

public:
	using Component::Component;

	std::weak_ptr<Component_ScoreManager> score_manager;
	std::weak_ptr<Component_Transform> player_transform;
	float grace_period = 1;

	// Spawns asteroid with randomized values.
	void SpawnEnemyShip();

	// Explodes all asteroids in the scene.
	void DespawnEnemyShips();

	inline bool Startable() const override { return false; }
	void Update() override;
};

