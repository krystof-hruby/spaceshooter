// Scene_Level1.cpp
// Krystof Hruby
// 2023

#include "Scene_Level1.h"

#include "AudioPlayer.h"
#include "Component_AsteroidsManager.h"
#include "Component_BackgroundController.h"
#include "Component_Level1Manager.h"
#include "Component_PlayerController.h"
#include "Component_Transform.h"
#include "Constants.h"
#include "Debugging.h"
#include "GameObjectFactory.h"
#include "Logging.h"
#include "Scene_Level2.h"
#include "SceneManager.h"
#include "Sprites.h"
#include "Time.h"

void Scene_Level1::Load() {
	LOG("LEVEL 1: Loading level 1. Scene UUID: " + std::to_string(this->GetID()));
	
	// Background.
	std::shared_ptr<GameObject> background = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Background, this->component_registry);
	background->GetComponent<Component_SpriteRenderer>()->SetSprite(SPRITE_BACKGROUND_BLACK);
	Scene::Instantiate(background);

	// Commander UI.
	std::shared_ptr<GameObject> commander_ui = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::UI_Commander, this->component_registry);
	Scene::Instantiate(commander_ui);

	// Text UI.
	std::shared_ptr<GameObject> text_ui = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::UI_Text, this->component_registry);
	Scene::Instantiate(text_ui);

	// Level manager.
	std::shared_ptr<GameObject> level1manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Level1Manager, this->component_registry);
	level1manager->GetComponent<Component_Level1Manager>()->preparation_period = 6;
	level1manager->GetComponent<Component_Level1Manager>()->commander_ui_spawn_period = 4;
	level1manager->GetComponent<Component_Level1Manager>()->fade_in_period = 2;
	
	level1manager->GetComponent<Component_Level1Manager>()->component_registry = this->component_registry;
	level1manager->GetComponent<Component_Level1Manager>()->commander_ui = commander_ui;
	level1manager->GetComponent<Component_Level1Manager>()->text_ui = text_ui;
	


	level1manager->GetComponent<Component_Level1Manager>()->level_end_period = 10;
	level1manager->GetComponent<Component_Level1Manager>()->fade_out_period = 5;
	#if DIFFERENT_GOAL
		level1manager->GetComponent<Component_Level1Manager>()->score_manager->goal = GOAL;
	#else
		level1manager->GetComponent<Component_Level1Manager>()->score_manager->goal = 100;
	#endif
	level1manager->GetComponent<Component_Level1Manager>()->background_controller = background->GetComponent<Component_BackgroundController>();
	Scene::Instantiate(level1manager);
}

void Scene_Level1::Unload() {
	LOG("LEVEL 1: Unloading level 1. Scene UUID: " + std::to_string(this->GetID()));

	AudioPlayer::GetInstance().StopAllAudioClips();
}

