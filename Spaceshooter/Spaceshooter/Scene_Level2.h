// Scene_Level2.h
// Krystof Hruby
// 2023

#pragma once

#include <vector>

#include "Scene.h"
#include "ScoreManager.h"

// Scene for level 2 of the game.
class Scene_Level2 final : public Scene {
private:
	std::shared_ptr<ScoreManager> score_manager = std::make_shared<ScoreManager>();
	
	std::shared_ptr<GameObject> background;
	std::shared_ptr<GameObject> player;
	std::vector<std::shared_ptr<GameObject>> asteroids;
	std::vector<std::shared_ptr<GameObject>> enemy_ships;
	// Must have ownership of all scene objects. Give to player controller to spawn bullets.
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> bullets = std::make_shared<std::vector<std::shared_ptr<GameObject>>>();

	#if LOWER_GOAL
		int goal = GOAL;
	#else
		int goal = 50;
	#endif
	bool reached_goal = false;

	float grace_period = 1;
	float grace_period_time = 0;

	// Spawns asteroid with randomized values.
	void SpawnAsteroid();
	float asteroid_spawn_period = 1;
	float asteroid_spawn_time = 0;

	// Spawns enemy ship with randomized values.
	void SpawnEnemyShip();
	float enemy_ship_spawn_period = 1;
	float enemy_ship_spawn_time = 0;

public:
	void Load() override;
	void Update() override;
	void Unload() override;
};

