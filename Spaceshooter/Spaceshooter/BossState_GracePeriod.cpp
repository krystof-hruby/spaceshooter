// BossState_GracePeriod.cpp
// Krystof Hruby
// 2023

#include "BossState_GracePeriod.h"

#include "Component_BossController.h"
#include "Time.h"

void BossState_GracePeriod::Play(std::shared_ptr<Component_BossController> boss_controller) {
	if (this->grace_period_time > boss_controller->grace_period)
		boss_controller->ChangeState(boss_controller->state_movig_to_floating_spot);

	this->grace_period_time += (float)Time::delta_time;
}
