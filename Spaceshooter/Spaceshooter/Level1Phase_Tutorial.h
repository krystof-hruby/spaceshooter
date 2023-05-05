// Leve1Phase_Tutorial.h
// Krystof Hruby
// 2023

#pragma once

#include "Level1Phase.h"

class Level1Phase_Tutorial : public Level1Phase {
public:
	void Play(std::shared_ptr<Component_Level1Manager> level1manager);

private:
	bool commander_spawned = false;
	bool warped_player_in = false;
};

