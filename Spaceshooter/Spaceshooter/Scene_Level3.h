// Scene_Level3.h
// Krystof Hruby
// 2023

#pragma once

#include "Scene.h"

// Scene for level 3 of the game.
class Scene_Level3 final : public Scene {
public:
	void Load() override;
	void Update() override;
	void Unload() override;
};

