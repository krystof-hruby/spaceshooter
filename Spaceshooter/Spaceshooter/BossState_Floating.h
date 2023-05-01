// BossState_Floating.h
// Krystof Hruby
// 2023

#pragma once

#include "BossState.h"
#include "vector2D.h"

class BossState_Floating final : public BossState {
public:
	void Play(std::shared_ptr<Component_BossController> boss_controller) override;
	void RandomizeMovementDirection();

private:
	float floating_time = 0;
	float moving_to_floating_spot_time = 0;
	float attack_time = 0;
	Vector2D movement_direction;
};

