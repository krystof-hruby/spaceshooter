// Scene_Level1.h
// Krystof Hruby
// 2023

#pragma once

#include "Scene.h"
#include "Component_PlayerController.h"

// Scene for level 1 of the game.
class Scene_Level1 final : public Scene {
public:
	void Load() override;
	void Update() override;
	void Unload() override;

private:
	std::weak_ptr<Component_PlayerController> player_controller;
};

