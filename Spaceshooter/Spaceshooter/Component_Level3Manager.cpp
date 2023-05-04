// Component_Level3Manager.cpp
// Krystof Hruby
// 2023

#include "Component_Level3Manager.h"

#include "Time.h"

void Component_Level3Manager::Update() {
	if (this->score_manager->ReachedGoal()) {
		if (this->level_end_time > this->fade_out_period)
			this->background_controller.lock()->FadeOut();

		if (this->level_end_time > this->level_end_period)
			return; // TODO: end game

		this->level_end_time += (float)Time::delta_time;
	}
}
