// Leve1Phase_Preparation.cpp
// Krystof Hruby
// 2023

#include "Level1Phase_Preparation.h"

#include "Component_Animator.h"
#include "Component_Level1Manager.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "Time.h"

void Level1Phase_Preparation::Play(std::shared_ptr<Component_Level1Manager> level1manager) {
	// Fade in background.
	if (this->preparation_time > level1manager->fade_in_period)
		level1manager->background_controller.lock()->FadeIn();

	
	if (this->preparation_time > level1manager->commander_ui_spawn_period) {
		level1manager->commander_ui.lock()->GetComponent<Component_Transform>()->scale += (float)Time::delta_time * 10;
	
		if (level1manager->commander_ui.lock()->GetComponent<Component_Transform>()->scale >= 0.4f)
			level1manager->commander_ui.lock()->GetComponent<Component_Transform>()->scale = 0.4f;
	}

	// Change state to tutorial when finished.
	if (this->preparation_time > level1manager->preparation_period) {
		level1manager->commander_ui.lock()->GetComponent<Component_Animator>()->PlayAnimation("commander spawn");
		level1manager->ChangePhase(level1manager->phase_tutorial);
	}

	this->preparation_time += (float)Time::delta_time;
}
