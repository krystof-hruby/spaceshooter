// Scene_Level1.cpp
// Krystof Hruby
// 2023

#include "Scene_Level1.h"

#include "Component_AsteroidsManager.h"
#include "Component_PlayerController.h"
#include "Component_ScoreManager.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"
#include "Constants.h"
#include "GameObjectFactory.h"
#include "Logging.h"
#include "Scene_Level2.h"
#include "SceneManager.h"
#include "Sprites.h"
#include "Time.h"

void Scene_Level1::Load() {
	LOG("LEVEL 1: Loading level 1. Scene UUID: " + std::to_string(this->GetID()));
	
	// Score manager.
	std::shared_ptr<GameObject> score_manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::ScoreManager, this->component_registry);
	Scene::Instantiate(score_manager);

	// Background.
	std::shared_ptr<GameObject> background = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Background, this->component_registry);
	background->GetComponent<Component_SpriteRenderer>()->SetSprite(SPRITE_BACKGROUND_BLACK);
	Scene::Instantiate(background);
	
	// Player.
	std::shared_ptr<GameObject> player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, this->component_registry);
	player->GetComponent<Component_PlayerController>()->score_manager = score_manager->GetComponent<Component_ScoreManager>();
	Scene::Instantiate(player);
	this->player_controller = player->GetComponent<Component_PlayerController>();

	// Asteroids manager.
	std::shared_ptr<GameObject> asteroids_manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::AsteroidsManager, this->component_registry);
	asteroids_manager->GetComponent<Component_AsteroidsManager>()->score_manager = score_manager->GetComponent<Component_ScoreManager>();
	asteroids_manager->GetComponent<Component_AsteroidsManager>()->grace_period = 7;
	Scene::Instantiate(asteroids_manager);
}

void Scene_Level1::Update() {
	if (this->player_controller.lock()->Despawned())
		SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level2>());
}

void Scene_Level1::Unload() {
	LOG("LEVEL 1: Unloading level 1. Scene UUID: " + std::to_string(this->GetID()));

	this->StopAllSounds();
}

