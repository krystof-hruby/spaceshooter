// Level1Phases.cpp
// Krystof Hruby
// 2023

#include "Level1Phases.h"

#include "Component_Animator.h"
#include "Component_AsteroidsManager.h"
#include "Component_Level1Manager.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Scene.h"
#include "Time.h"

void Level1Phase_Preparation::Play(std::shared_ptr<Component_Level1Manager> level1manager) {
	// Fade in background.
	if (this->preparation_time > level1manager->fade_in_period)
		level1manager->background_controller.lock()->FadeIn();

	if (this->preparation_time > level1manager->commander_ui_spawn_period)
		level1manager->ui_controller.lock()->SpawnCommanderFrame();

	// Change state to tutorial when finished.
	if (this->preparation_time > level1manager->preparation_period) {
		level1manager->ui_controller.lock()->PlayLevel1IntroAndTutorial();
		level1manager->ChangePhase(level1manager->phase_intro);
	}

	this->preparation_time += (float)Time::delta_time;
}

void Level1Phase_Intro::Play(std::shared_ptr<Component_Level1Manager> level1manager) {
	if (!this->player_spawned && this->player_spawn_time > level1manager->player_spawn_period) {
		std::shared_ptr<GameObject> player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, level1manager->component_registry.lock());
		Scene::Instantiate(player);

		this->player_spawned = true;
	}
	this->player_spawn_time += (float)Time::delta_time;
	
	if (level1manager->ui_controller.lock()->Level1IntroFinished())
		level1manager->ChangePhase(level1manager->phase_tutorial);
}

void Level1Phase_Tutorial::Play(std::shared_ptr<Component_Level1Manager> level1manager) {
	if (!this->asteroids_spawned && this->asteroids_spawn_time > level1manager->asteroids_spawn_period) {
		std::shared_ptr<GameObject> asteroids_manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::AsteroidsManager, level1manager->component_registry.lock());
		Scene::Instantiate(asteroids_manager);

		this->asteroids_spawned = true;
	}
	this->asteroids_spawn_time += (float)Time::delta_time;
	
	if (level1manager->ui_controller.lock()->Level1TutorialFinished())
		level1manager->ChangePhase(level1manager->phase_gameplay);
}

void Level1Phase_Gameplay::Play(std::shared_ptr<Component_Level1Manager> level1manager) {
	this->gameplay_time += (float)Time::delta_time;

	if (!this->passed14 && this->gameplay_time > level1manager->level_length / 4) {
		level1manager->ui_controller.lock()->PlayLevel1Cutscene1();
		this->passed14 = true;
	} else if (!this->passed12 && this->gameplay_time > level1manager->level_length / 2) {
		level1manager->ui_controller.lock()->PlayLevel1Cutscene2();
		this->passed12 = true;
	} else if (!this->passed34 && this->gameplay_time > level1manager->level_length * 3 / 4) {
		level1manager->ui_controller.lock()->PlayLevel1Cutscene3();
		this->passed34 = true;
	} else if (this->gameplay_time > level1manager->level_length) {
		level1manager->ui_controller.lock()->PlayLevel1Outro();
		level1manager->ChangePhase(level1manager->phase_outro);
	}
}

void Level1Phase_Outro::Play(std::shared_ptr<Component_Level1Manager> level1manager) {
}
