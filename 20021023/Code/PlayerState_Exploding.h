// PlayerState_Exploding.h
// Krystof Hruby
// 2023

#pragma once

#include "PlayerState.h"

class PlayerState_Exploding final : public PlayerState {
public:
	void Play(std::shared_ptr<Component_PlayerController> player_controller) override;
};

