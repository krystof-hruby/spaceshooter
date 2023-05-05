// Component_Level1Manager.cpp
// Krystof Hruby
// 2023

#include "Component_Level1Manager.h"

#include "Component_Animator.h"
#include "GameObject.h"
#include "Scene_Level2.h"
#include "SceneManager.h"
#include "Time.h"

void Component_Level1Manager::Start() {
	this->current_phase = phase_preparation;
}

void Component_Level1Manager::Update() {
	this->current_phase->Play(this->shared_from_this());


	/*if (this->score_manager->ReachedGoal()) {
		if (this->level_end_time > this->fade_out_period)
			this->background_controller.lock()->FadeOut();

		if (this->level_end_time > this->level_end_period)
			SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level2>());

		this->level_end_time += (float)Time::delta_time;
	}*/
}

void Component_Level1Manager::ChangePhase(std::shared_ptr<Level1Phase> phase) {
	this->current_phase = phase;
}
