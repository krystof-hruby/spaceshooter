// Component_EnemyShipsManager.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_Transform.h"

// Provides fields and methods for spawning enemy ships.
class Component_EnemyShipsManager final : public Component {
public:
	using Component::Component;
	inline bool Startable() const override { return false; }
	void Update() override;

	std::weak_ptr<Component_Transform> player_transform;
	float grace_period = 1;

	// Spawns enemy ship with randomized values.
	void SpawnEnemyShip();

private:
	float grace_period_time = 0;
	float enemy_ship_spawn_time = 0;
	float enemy_ship_spawn_period = 1; // Is randomized.
	bool enemy_ships_despawned = false;
};

