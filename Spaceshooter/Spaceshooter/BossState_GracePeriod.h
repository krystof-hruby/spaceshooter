// BossState_GracePeriod.h
// Krystof Hruby
// 2023

#pragma once

#include "BossState.h"

class BossState_GracePeriod final : public BossState {
private:
	float grace_period_time = 0;

public:
	void Play(std::shared_ptr<Component_BossController> boss_controller) override;
};

