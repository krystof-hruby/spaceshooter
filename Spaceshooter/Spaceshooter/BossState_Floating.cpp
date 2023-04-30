// BossState_Floating.cpp
// Krystof Hruby
// 2023

#include "BossState_Floating.h"

#include "Component_BossController.h"
#include "GameObject.h"
#include "Time.h"

void BossState_Floating::Play(std::shared_ptr<Component_BossController> boss_controller) {
	auto transform = boss_controller->GetGameObject()->GetComponent<Component_Transform>();

	this->floating_time += (float)Time::delta_time;
	transform->position.XValue = boss_controller->current_floating_spot.XValue + (sin(this->floating_time * 2) * boss_controller->floating_movement_speed);
	transform->position.YValue = boss_controller->current_floating_spot.YValue + (sin(this->floating_time * 1) * boss_controller->floating_movement_speed);

	// Shoot lasers.
	if (this->laser_shoot_time > boss_controller->lasers_shoot_period) {
		boss_controller->ShootLasers();
		this->laser_shoot_time = 0;
	}

	// Shoot homing missiles.
	if (this->homing_missile_shoot_time > boss_controller->homing_missile_shoot_period) {
		boss_controller->ShootHomingMissile();
		this->homing_missile_shoot_time = 0;
	}

	// Time to move to another spot.
	if (this->moving_to_floating_spot_time > boss_controller->moving_to_floating_spot_period) {
		boss_controller->ChangeState(boss_controller->state_movig_to_floating_spot);

		// Reset times.
		this->floating_time = 0;
		this->laser_shoot_time = 0;
		this->homing_missile_shoot_time = 0;
		this->moving_to_floating_spot_time = 0;
	}

	this->moving_to_floating_spot_time += (float)Time::delta_time;
	this->laser_shoot_time += (float)Time::delta_time;
	this->homing_missile_shoot_time += (float)Time::delta_time;
}
