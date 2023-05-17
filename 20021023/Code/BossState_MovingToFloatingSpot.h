// BossState_MovingToFloatingSpot.h
// Krystof Hruby
// 2023

#pragma once

#include "BossState.h"
#include "vector2D.h"

class BossState_MovingToFloatingSpot final : public BossState {
private:
	int next_floating_spot = 0;

	bool IsAtFloatingSpot(Vector2D position, Vector2D floating_spot) const;

public:
	void Play(std::shared_ptr<Component_BossController> boss_controller) override;
};

