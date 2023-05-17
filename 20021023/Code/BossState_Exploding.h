// BossState_Exploding.h
// Krystof Hruby
// 2023

#pragma once

#include "BossState.h"

class BossState_Exploding final : public BossState {
public:
	void Play(std::shared_ptr<Component_BossController> boss_controller) override;
};

