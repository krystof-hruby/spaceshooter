// Scene_Level2.cpp
// Krystof Hruby
// 2023

#include "Scene_Level2.h"

#include "AudioClips.h"
#include "Component_AsteroidsManager.h"
#include "Component_EnemyShipsManager.h"
#include "Component_Level2Manager.h"
#include "Component_PlayerController.h"
#include "GameObjectFactory.h"
#include "Logging.h"
#include "Sprites.h"

void Scene_Level2::Load() {
	LOG("LEVEL 2: Loading level 2. Scene UUID: " + std::to_string(this->GetID()));

	/*

	// Background.
	std::shared_ptr<GameObject> background = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Background, this->component_registry);
	background->GetComponent<Component_SpriteRenderer>()->SetSprite(SPRITE_BACKGROUND_BROWN);
	Scene::Instantiate(background);

	// Level manager.
	std::shared_ptr<GameObject> level2manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Level2Manager, this->component_registry);
	level2manager->GetComponent<Component_Level2Manager>()->level_end_period = 10;
	level2manager->GetComponent<Component_Level2Manager>()->fade_out_period = 5;
	#if DIFFERENT_GOAL
		level2manager->GetComponent<Component_Level2Manager>()->score_manager->goal = GOAL;
	#else
		level2manager->GetComponent<Component_Level2Manager>()->score_manager->goal = 100;
	#endif
	level2manager->GetComponent<Component_Level2Manager>()->background_controller = background->GetComponent<Component_BackgroundController>();
	Scene::Instantiate(level2manager);

	// Player.
	std::shared_ptr<GameObject> player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, this->component_registry);
	Scene::Instantiate(player);

	// Asteroids manager.
	std::shared_ptr<GameObject> asteroids_manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::AsteroidsManager, this->component_registry);
	asteroids_manager->GetComponent<Component_AsteroidsManager>()->score_manager = level2manager->GetComponent<Component_Level2Manager>()->score_manager;
	Scene::Instantiate(asteroids_manager);

	// Enemy ships manager.
	std::shared_ptr<GameObject> enemy_ships_manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::EnemyShipsManager, this->component_registry);
	enemy_ships_manager->GetComponent<Component_EnemyShipsManager>()->player_transform = player->GetComponent<Component_Transform>();
	enemy_ships_manager->GetComponent<Component_EnemyShipsManager>()->grace_period = 7;
	enemy_ships_manager->GetComponent<Component_EnemyShipsManager>()->score_manager = level2manager->GetComponent<Component_Level2Manager>()->score_manager;
	Scene::Instantiate(enemy_ships_manager);

	*/
}

void Scene_Level2::Unload() {
	LOG("LEVEL 2: Unloading level 2. Scene UUID: " + std::to_string(this->GetID()));

	AudioPlayer::GetInstance().StopAllAudioClips();
}
