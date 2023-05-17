// PlayerState_Flying.h
// Krystof Hruby
// 2023

#pragma once

#include "PlayerState.h"

class PlayerState_Flying : public PlayerState {
public:
	void Play(std::shared_ptr<Component_PlayerController> player_controller) override;

private:
	float reload_time = 0;
	float free_roaming_time = 0;
};

