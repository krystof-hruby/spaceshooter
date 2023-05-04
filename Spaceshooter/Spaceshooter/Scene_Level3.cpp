// Scene_Level3.cpp
// Krystof Hruby
// 2023

#include "Scene_Level3.h"

#include "AudioClips.h"
#include "Component_BossController.h"
#include "Component_PlayerController.h"
#include "Component_Level3Manager.h"
#include "GameObjectFactory.h"
#include "Logging.h"
#include "Sprites.h"

void Scene_Level3::Load() {
	LOG("LEVEL 3: Loading level 3. Scene UUID: " + std::to_string(this->GetID()));

	// Background.
	std::shared_ptr<GameObject> background = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Background, this->component_registry);
	background->GetComponent<Component_SpriteRenderer>()->SetSprite(SPRITE_BACKGROUND_PURPLE);
	Scene::Instantiate(background);

	// Level manager.
	std::shared_ptr<GameObject> level3manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Level3Manager, this->component_registry);
	level3manager->GetComponent<Component_Level3Manager>()->level_end_period = 10;
	level3manager->GetComponent<Component_Level3Manager>()->fade_out_period = 5;
	level3manager->GetComponent<Component_Level3Manager>()->background_controller = background->GetComponent<Component_BackgroundController>();
	Scene::Instantiate(level3manager);

	// Player.
	std::shared_ptr<GameObject> player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, this->component_registry);
	player->GetComponent<Component_PlayerController>()->score_manager = level3manager->GetComponent<Component_Level3Manager>()->score_manager;
	Scene::Instantiate(player);

	// Boss.
	std::shared_ptr<GameObject> boss = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Boss, this->component_registry);
	boss->GetComponent<Component_BossController>()->player_transform = player->GetComponent<Component_Transform>();
	boss->GetComponent<Component_BossController>()->grace_period = 6;
	boss->GetComponent<Component_BossController>()->score_manager = level3manager->GetComponent<Component_Level3Manager>()->score_manager;
	Scene::Instantiate(boss);
}

void Scene_Level3::Unload() {
	LOG("LEVEL 3: Unloading level 3. Scene UUID: " + std::to_string(this->GetID()));

	AudioPlayer::GetInstance().StopAllAudioClips();
}
