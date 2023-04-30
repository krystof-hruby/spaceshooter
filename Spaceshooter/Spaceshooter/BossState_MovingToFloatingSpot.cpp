// BossState_MovingToFloatingSpot.cpp
// Krystof Hruby
// 2023

#include "BossState_MovingToFloatingSpot.h"

#include "Component_BossController.h"
#include "GameObject.h"
#include "Time.h"

void BossState_MovingToFloatingSpot::Play(std::shared_ptr<Component_BossController> boss_controller) {
	auto transform = boss_controller->GetGameObject()->GetComponent<Component_Transform>();
	Vector2D next_floating_spot = boss_controller->floating_spots[this->next_floating_spot];

	// Interpolate between current position and next floating spot.
	float time_step = (float)Time::delta_time * boss_controller->movement_speed;
	transform->position.XValue = (1 - time_step) * transform->position.XValue + time_step * next_floating_spot.XValue;
	transform->position.YValue = (1 - time_step) * transform->position.YValue + time_step * next_floating_spot.YValue;

	if (this->IsAtFloatingSpot(transform->position, next_floating_spot)) {
		boss_controller->ChangeState(boss_controller->state_floating);

		// Update current floating spot to current position (is slightly different).
		boss_controller->current_floating_spot = transform->position;
		
		// Randomly choose next floating spot that is not the current floating spot.
		int current_floating_spot = this->next_floating_spot;
		while (this->next_floating_spot == current_floating_spot)
			this->next_floating_spot = rand() % boss_controller->floating_spots.size();
	}
}

bool BossState_MovingToFloatingSpot::IsAtFloatingSpot(Vector2D position, Vector2D floating_spot) const {
	// Check if it is near floating spot to avoid weird sprite rendering effects.
	float delta = 40;
	bool is_at_x = (position.XValue >= (floating_spot.XValue - delta)) && (position.XValue <= (floating_spot.XValue + delta));
	bool is_at_y = (position.YValue >= (floating_spot.YValue - delta)) && (position.YValue <= (floating_spot.YValue + delta));

	return is_at_x && is_at_y;
}
