// Scene_Level1.h
// Krystof Hruby
// 2023

#pragma once

#include "AsteroidsManager.h"
#include "Debugging.h"
#include "Scene_LevelBase.h"

// Scene for level 1 of the game.
class Scene_Level1 final : public Scene_LevelBase, public AsteroidsManager {
public:
	void Load() override;
	void Update() override;
	void Unload() override;
};

