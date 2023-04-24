// Scene_Level1.cpp
// Krystof Hruby
// 2023

#include "Scene_Level1.h"

#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Logging.h"
#include "SceneManager.h"
#include "Scene_Level2.h"
#include "Component_AsteroidCollider.h"
#include "Component_AsteroidController.h"
#include "Component_CircleCollider.h"
#include "Component_PlayerController.h"
#include "Component_RectangleCollider.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"

void Scene_Level1::Load() {
	LOG("LEVEL 1: Loading level 1. Scene UUID: " + std::to_string(this->GetID()));

	this->grace_period = 7;
	
	this->background = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Background, this->component_registry);
	this->background->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/backgrounds/background_black.bmp");

	this->player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, this->component_registry);
	this->player->GetComponent<Component_PlayerController>()->score_manager = this->score_manager;
}

void Scene_Level1::Update() {
	// Spawn asteroids after grace period.
	if ((this->grace_period_time > this->grace_period) && (this->asteroid_spawn_time > this->asteroid_spawn_period)) {
		SpawnAsteroid();
		this->asteroid_spawn_time = 0;
		this->asteroid_spawn_period = (float)(rand() % 10 / 9); // Randomize spawn period.
	}

	this->grace_period_time += (float)Time::delta_time;
	this->asteroid_spawn_time += (float)Time::delta_time;

	if (this->score_manager->score > 50) {
		for (auto asteroid : this->asteroids)
			asteroid->Destroy();

		// TODO: play some fancy animations or something before changing

		// SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level2>());
	}
}

void Scene_Level1::Unload() {
	LOG("LEVEL 1: Unloading level 1. Scene UUID: " + std::to_string(this->GetID()));

	this->StopAllSounds();
}


void Scene_Level1::SpawnAsteroid() {
	std::shared_ptr<GameObject> asteroid = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Asteroid, this->component_registry);

	// Randomize spawn position.
	float spawn_position_x = 0;
	float spawn_position_y = 0;
	if (rand() % 2 == 1) {
		spawn_position_x = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
		spawn_position_y = (float)(rand() % 2000 - 1000);
	} else {
		spawn_position_x = (float)(rand() % 2000 - 1000);
		spawn_position_y = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
	}
	asteroid->GetComponent<Component_Transform>()->position = Vector2D(spawn_position_x, spawn_position_y);

	// Randomize sprite.
	Sprite sprite = rand() % 2 == 1 ? L"assets/asteroids/asteroid_large.bmp" : L"assets/asteroids/asteroid_small.bmp";
	asteroid->GetComponent<Component_SpriteRenderer>()->SetSprite(sprite);

	// Randomize scale.
	asteroid->GetComponent<Component_Transform>()->scale = ((float)((rand() % 3) + 2) / 10);
	int scale_multiplier = sprite == L"assets/asteroids/asteroid_large.bmp" ? 190 : 250;
	asteroid->GetComponent<Component_AsteroidCollider>()->radius = asteroid->GetComponent<Component_Transform>()->scale * scale_multiplier;

	// Randomize values.
	Vector2D movement_direction;
	movement_direction.XValue = spawn_position_x < 0 ? (float)(rand() % 10) : -(float)(rand() % 10);
	movement_direction.YValue = spawn_position_y < 0 ? (float)(rand() % 10) : -(float)(rand() % 10);
	asteroid->GetComponent<Component_AsteroidController>()->movement_direction = movement_direction;
	asteroid->GetComponent<Component_AsteroidController>()->movement_speed = (float)(rand() % 100);
	asteroid->GetComponent<Component_AsteroidController>()->rotation_speed = (float)(rand() % 5 + 1);
	asteroid->GetComponent<Component_AsteroidController>()->rotation_direction = rand() % 2 == 1 ? CLOCKWISE: COUNTERCLOCKWISE;

	this->asteroids.push_back(asteroid);
}

