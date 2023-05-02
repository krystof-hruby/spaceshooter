// PlayerState_Spawning.h
// Krystof Hruby
// 2023

#pragma once

#include "PlayerState.h"

class PlayerState_Spawning final : public PlayerState {
public:
	void Play(std::shared_ptr<Component_PlayerController> player_controller) override;
};

