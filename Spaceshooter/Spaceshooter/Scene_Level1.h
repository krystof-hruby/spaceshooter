// Scene_Level1.h
// Krystof Hruby
// 2023

#pragma once

#include "Scene.h"

// Scene for level 1 of the game.
class Scene_Level1 final : public Scene {
private:
	std::shared_ptr<GameObject> player;

public:
	void Load() override;
	void Update() override;
	void Unload() override;
};

