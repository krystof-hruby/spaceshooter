// BossState_Floating.cpp
// Krystof Hruby
// 2023

#include "BossState_Floating.h"

#include "Component_BossController.h"
#include "GameObject.h"
#include "Time.h"

void BossState_Floating::Play(std::shared_ptr<Component_BossController> boss_controller) {
	// Float.
	auto transform = boss_controller->GetGameObject()->GetComponent<Component_Transform>();
	transform->position.XValue = boss_controller->current_floating_spot.XValue + (sin(this->floating_time * 2) * boss_controller->floating_movement_speed);
	transform->position.YValue = boss_controller->current_floating_spot.YValue + (sin(this->floating_time * 1) * boss_controller->floating_movement_speed);

	// Attac.
	if (this->attack_time > boss_controller->attack_period) {
		switch (rand() % 3) {
		case 0:
		case 1:
			boss_controller->ShootHomingMissile();
			break;
		case 2:
			boss_controller->SpawnMines();
			break;
		//case 1:
			//boss_controller->ShootLasers();
			//break;
		}

		this->attack_time = 0;
	}
	this->attack_time += (float)Time::delta_time;
	
	// Time to move to another spot.
	if (this->moving_to_floating_spot_time > boss_controller->moving_to_floating_spot_period) {
		boss_controller->ChangeState(boss_controller->state_movig_to_floating_spot);

		// Reset for next floating time.
		this->floating_time = 0;
		this->moving_to_floating_spot_time = 0;
	}
	this->floating_time += (float)Time::delta_time;
	this->moving_to_floating_spot_time += (float)Time::delta_time;
}
