// PlayerState_GracePeriod.h
// Krystof Hruby
// 2023

#pragma once

#include "PlayerState.h"

class PlayerState_GracePeriod final : public PlayerState {
public:
	void Play(std::shared_ptr<Component_PlayerController> player_controller) override;

private:
	float grace_period_time = 0;
};

