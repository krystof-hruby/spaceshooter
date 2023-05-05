// Level1Phase_Preparation.h
// Krystof Hruby
// 2023

#pragma once

#include "Level1Phase.h"

class Level1Phase_Preparation : public Level1Phase {
public:
	void Play(std::shared_ptr<Component_Level1Manager> level1manager) override;

private:
	float preparation_time = 0;
};

