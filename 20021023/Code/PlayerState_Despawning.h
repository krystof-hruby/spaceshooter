// PlayerState_Despawning.h
// Krystof Hruby
// 2023

#pragma once

#include "PlayerState.h"

class PlayerState_Despawning : public PlayerState {
public:
	void Play(std::shared_ptr<Component_PlayerController> player_controller) override;

private:
	float free_roaming_time = 0;
};

