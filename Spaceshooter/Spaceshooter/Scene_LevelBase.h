// Scene_LevelBase.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_SpriteRenderer.h"
#include "Debugging.h"
#include "Scene.h"
#include "ScoreManager.h"
#include "vector2D.h"

// Provides base fields and methods used by all levels.
class Scene_LevelBase : public Scene {
protected:
	std::shared_ptr<ScoreManager> score_manager = std::make_shared<ScoreManager>();

	std::shared_ptr<GameObject> background;
	std::shared_ptr<GameObject> player;
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

	// Loads in background.
	void SetupBackground(Sprite background_sprite);
	// Loads in player.
	void SetupPlayer();
	// Returns a random spawn position outside of the screen.
	Vector2D GetRandomSpawnPosition();
};

