// Component_EnemyShipsManager.h
// Krystof Hruby
// 2023

#pragma once

#include <vector>
#include "Component_Transform.h"

class Component_EnemyShipsManager final : public Component {
public:
	using Component::Component;
	inline bool Startable() const override { return false; }
	void Update() override;

	std::weak_ptr<Component_Transform> player_transform;
	float grace_period = 1;

	// Spawns asteroid with randomized values.
	void SpawnEnemyShip();

	// Explodes all asteroids in the scene.
	void DespawnEnemyShips();

private:
	float grace_period_time = 0;
	float enemy_ship_spawn_time = 0;
	float enemy_ship_spawn_period = 1; // Is randomized.
	bool enemy_ships_despawned = false;
	std::vector<std::weak_ptr<GameObject>> enemy_ships;
};

