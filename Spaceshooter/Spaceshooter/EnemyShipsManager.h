// EnemyShipsManager.h
// Krystof Hruby
// 2023

#pragma once

#include <vector>

#include "GameObject.h"

// Provides fields and methods to manage enemy ships.
class EnemyShipsManager {
private:
	std::vector<std::shared_ptr<GameObject>> enemy_ships;
	float enemy_ship_spawn_period = 1;
	float enemy_ship_spawn_time = 0;

protected:
	// Spawns enemy ship with randomized values.
	void SpawnEnemyShip(Vector2D spawn_position, std::shared_ptr<GameObject> player, std::shared_ptr<ComponentRegistry> component_registry);

	// Explodes all enemy ships in the scene.
	void DespawnEnemyShips();
};

