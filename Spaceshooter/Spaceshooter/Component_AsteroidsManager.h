// Component_AsteroidsManager.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"

// Provides fields and methods for spawning and managing asteroids.
class Component_AsteroidsManager final : public Component {
public:
	using Component::Component;
	inline bool Startable() const override { return false; }
	void Update() override;

	// Spawns asteroid with randomized values.
	void SpawnAsteroid();

private:
	float asteroid_spawn_time = 0;
	float asteroid_spawn_period = 1; // Is randomized.
};

