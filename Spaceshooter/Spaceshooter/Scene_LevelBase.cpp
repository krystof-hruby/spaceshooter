// Scene_LevelBase.h
// Krystof Hruby
// 2023

#include "Scene_LevelBase.h"

#include "Component_PlayerController.h"
#include "GameObjectFactory.h"

void Scene_LevelBase::SetupBackground(Sprite background_sprite) {
	this->background = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Background, this->component_registry);
	this->background->GetComponent<Component_SpriteRenderer>()->SetSprite(background_sprite);
	#if VISUALIZE_HITBOXES
		this->background->GetComponent<Component_SpriteRenderer>()->is_active = false;
	#endif
}

void Scene_LevelBase::SetupPlayer() {
	this->player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, this->component_registry);
	this->player->GetComponent<Component_PlayerController>()->score_manager = this->score_manager;
	this->player->GetComponent<Component_PlayerController>()->bullets = this->bullets;
}

Vector2D Scene_LevelBase::GetRandomSpawnPosition() {
	Vector2D spawn_position;

	if (rand() % 2 == 1) {
		spawn_position.XValue = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
		spawn_position.YValue = (float)(rand() % 2000 - 1000);
	}
	else {
		spawn_position.XValue = (float)(rand() % 2000 - 1000);
		spawn_position.YValue = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
	}

	return spawn_position;
}
