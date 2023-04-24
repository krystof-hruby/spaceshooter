// Scene_Level1.h
// Krystof Hruby
// 2023

#pragma once

#include <vector>

#include "Scene.h"
#include "ScoreManager.h"

// Scene for level 1 of the game.
class Scene_Level1 final : public Scene {
private:
	std::shared_ptr<ScoreManager> score_manager = std::make_shared<ScoreManager>();

	std::shared_ptr<GameObject> player;
	std::vector<std::shared_ptr<GameObject>> asteroids;
	std::shared_ptr<GameObject> background;

	float grace_period = 1;
	float grace_period_time = 0;

	float asteroid_spawn_period = 1;
	float asteroid_spawn_time = 0;

	// Spawns asteroid with randomized values.
	void SpawnAsteroid();

public:
	void Load() override;
	void Update() override;
	void Unload() override;
};

