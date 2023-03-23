// Scene_Level2.h
// Krystof Hruby
// 2023

#pragma once

#include "Scene.h"

// Scene for level 2 of the game.
class Scene_Level2 final : public Scene {
public:
	void Load() override;
	void Update() override;
	void Unload() override;
};

