// Scene_Level1.cpp
// Krystof Hruby
// 2023

#include "Logging.h" // TODO: remove

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

	this->player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, this->component_registry);
	this->player->GetComponent<Component_PlayerController>()->score_manager = this->score_manager;
	this->grace_period = 7;
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

	if (this->score_manager->score > 50)
		SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level2>());
}

void Scene_Level1::Unload() {
	LOG("LEVEL 1: Unloading level 1. Scene UUID: " + std::to_string(this->GetID()));

	LOG(this->score_manager->score);

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
	asteroid->GetComponent<Component_Transform>()->scale = (float)((rand() % 80 + 50)) / 300;

	asteroid->GetComponent<Component_AsteroidCollider>()->radius = asteroid->GetComponent<Component_Transform>()->scale * 200;

	// Randomize sprite.
	switch (rand() % 5) {
	case 0:
		asteroid->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/asteroids/asteroid1.bmp");
	case 1:
		asteroid->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/asteroids/asteroid2.bmp");
	case 2:
		asteroid->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/asteroids/asteroid3.bmp");
	case 3:
		asteroid->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/asteroids/asteroid4.bmp");
	case 4:
		asteroid->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/asteroids/asteroid5.bmp");
	}

	// Randomize values.
	asteroid->GetComponent<Component_AsteroidController>()->movement_direction = Vector2D((float)(rand() % 10 - 5), (float)(rand() % 10 - 5));
	asteroid->GetComponent<Component_AsteroidController>()->movement_speed = (float)(rand() % 200);
	asteroid->GetComponent<Component_AsteroidController>()->rotation_speed = (float)(rand() % 5 + 1);
	if (rand() % 2 == 1)
		asteroid->GetComponent<Component_AsteroidController>()->rotation_direction = CLOCKWISE;
	else
		asteroid->GetComponent<Component_AsteroidController>()->rotation_direction = COUNTERCLOCKWISE;

	this->asteroids.push_back(asteroid);
}

