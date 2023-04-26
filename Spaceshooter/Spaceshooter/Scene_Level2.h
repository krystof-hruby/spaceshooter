// Scene_Level2.h
// Krystof Hruby
// 2023

#pragma once

#include "AsteroidsManager.h"
#include "Debugging.h"
#include "EnemyShipsManager.h"
#include "Scene_LevelBase.h"
#include "ScoreManager.h"

// Scene for level 2 of the game.
class Scene_Level2 final : public Scene_LevelBase, public AsteroidsManager, public EnemyShipsManager {
public:
	void Load() override;
	void Update() override;
	void Unload() override;
};

