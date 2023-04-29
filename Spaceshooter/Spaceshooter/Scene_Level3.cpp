// Scene_Level3.cpp
// Krystof Hruby
// 2023

#include "Scene_Level3.h"

#include "Component_AsteroidsManager.h"
#include "Component_BossController.h"
#include "Component_EnemyShipsManager.h"
#include "Component_PlayerController.h"
#include "Component_ScoreManager.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"
#include "Constants.h"
#include "GameObjectFactory.h"
#include "Logging.h"
#include "Time.h"

void Scene_Level3::Load() {
	LOG("LEVEL 3: Loading level 3. Scene UUID: " + std::to_string(this->GetID()));

	// Score manager.
	std::shared_ptr<GameObject> score_manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::ScoreManager, this->component_registry);
	Scene::Instantiate(score_manager);

	// Background.
	std::shared_ptr<GameObject> background = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Background, this->component_registry);
	background->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/backgrounds/background_black.png");
	Scene::Instantiate(background);

	// Player.
	std::shared_ptr<GameObject> player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, this->component_registry);
	player->GetComponent<Component_PlayerController>()->score_manager = score_manager->GetComponent<Component_ScoreManager>();
	Scene::Instantiate(player);

	// Boss.
	std::shared_ptr<GameObject> boss = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Boss, this->component_registry);
	boss->GetComponent<Component_BossController>()->player_transform = player->GetComponent<Component_Transform>();
	boss->GetComponent<Component_BossController>()->grace_period = 3;
	Scene::Instantiate(boss);
}

void Scene_Level3::Update() {

}

void Scene_Level3::Unload() {
	LOG("LEVEL 3: Unloading level 3. Scene UUID: " + std::to_string(this->GetID()));

	this->StopAllSounds();
}
