// Level1Phase_Gameplay.h
// Krystof Hruby
// 2023

#pragma once

#include "Level1Phase.h"

class Level1Phase_Gameplay : public Level1Phase {
public:
	void Play(std::shared_ptr<Component_Level1Manager> level1manager) override;

private:
	bool played_start = false;
	bool spawned_asteroids_manager = false;
};

