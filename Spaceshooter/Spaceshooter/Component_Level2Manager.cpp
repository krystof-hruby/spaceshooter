// Component_Level2Manager.cpp
// Krystof Hruby
// 2023

#include "Component_Level2Manager.h"

#include "Time.h"
#include "Scene_Level3.h"
#include "SceneManager.h"

void Component_Level2Manager::Start() {
}

void Component_Level2Manager::Update() {
	/*if (this->score_manager->ReachedGoal()) {
		if (this->level_end_time > this->fade_out_period)
			this->background_controller.lock()->FadeOut();

		if (this->level_end_time > this->level_end_period)
			SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level3>());

		this->level_end_time += (float)Time::delta_time;
	}*/
}
