// AsteroidsManager.h
// Krystof Hruby
// 2023

#pragma once

#include <vector>

#include "GameObject.h"

// Provides field and method for spawning and managing asteroids.
class AsteroidsManager {
public:
	std::vector<std::shared_ptr<GameObject>> asteroids;
	float asteroid_spawn_period = 1;
	float asteroid_spawn_time = 0;

protected:
	// Spawns asteroid with randomized values.
	void SpawnAsteroid(Vector2D spawn_position, std::shared_ptr<ComponentRegistry> component_registry);

	// Explodes all asteroids in the scene.
	void DespawnAsteroids();
};

