// Component_AsteroidsManager.h
// Krystof Hruby
// 2023

#pragma once

#include <vector>
#include "Component_ScoreManager.h"

// Provides field and method for spawning and managing asteroids.
class Component_AsteroidsManager final : public Component {
private:
	float grace_period_time = 0;
	float asteroid_spawn_time = 0;
	float asteroid_spawn_period = 1; // Is randomized.
	bool asteroids_despawned = false;
	std::vector<std::weak_ptr<GameObject>> asteroids;

public:
	using Component::Component;

	std::weak_ptr<Component_ScoreManager> score_manager;
	float grace_period = 1;

	// Spawns asteroid with randomized values.
	void SpawnAsteroid();

	// Explodes all asteroids in the scene.
	void DespawnAsteroids();

	inline bool Startable() const override { return false; }
	void Update() override;
};

