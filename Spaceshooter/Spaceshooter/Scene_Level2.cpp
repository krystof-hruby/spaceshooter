// Scene_Level2.cpp
// Krystof Hruby
// 2023

#include "Scene_Level2.h"

#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Logging.h"
#include "SceneManager.h"
//#include "Scene_Level3.h"
#include "Component_AsteroidCollider.h"
#include "Component_AsteroidController.h"
#include "Component_CircleCollider.h"
#include "Component_EnemyShipCollider.h"
#include "Component_EnemyShipController.h"
#include "Component_PlayerController.h"
#include "Component_RectangleCollider.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"

void Scene_Level2::Load() {
	LOG("LEVEL 2: Loading level 2. Scene UUID: " + std::to_string(this->GetID()));

	this->grace_period = 7;
	this->asteroid_spawn_period = (float)((rand() % 10) + 1) / 8; // Randomize spawn period.
	this->enemy_ship_spawn_period = (float)((rand() % 10) + 1) / 5;

	this->background = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Background, this->component_registry);
	this->background->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/backgrounds/background_brown.bmp");
	#if VISUALIZE_HITBOXES
		this->background->GetComponent<Component_SpriteRenderer>()->is_active = false;
	#endif

	this->player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, this->component_registry);
	this->player->GetComponent<Component_PlayerController>()->score_manager = this->score_manager;
	this->player->GetComponent<Component_PlayerController>()->bullets = this->bullets;
}

void Scene_Level2::Update() {
	if (this->reached_goal)
		return;

	// Spawn asteroids after grace period.
	if ((this->grace_period_time > this->grace_period) && (this->asteroid_spawn_time > this->asteroid_spawn_period)) {
		this->SpawnAsteroid();
		this->asteroid_spawn_time = 0;
		this->asteroid_spawn_period = (float)((rand() % 10) + 1) / 8; // Randomize spawn period.
	}

	this->asteroid_spawn_time += (float)Time::delta_time;
	
	// Spawn enemy ships after grace period.
	if ((this->grace_period_time > this->grace_period) && (this->enemy_ship_spawn_time > this->enemy_ship_spawn_period)) {
		this->SpawnEnemyShip();
		this->enemy_ship_spawn_time = 0;
		this->enemy_ship_spawn_period = (float)((rand() % 10) + 1) / 5;
	}

	this->enemy_ship_spawn_time += (float)Time::delta_time;
	
	this->grace_period_time += (float)Time::delta_time;

	// End round when reached score.
	if (this->score_manager->score > this->goal) {
		for (auto asteroid : this->asteroids)
			if (asteroid->HasComponent<Component_AsteroidController>())
				asteroid->GetComponent<Component_AsteroidController>()->Explode();

		for (auto enemy_ship : this->enemy_ships)
			if (enemy_ship->HasComponent<Component_EnemyShipController>())
				enemy_ship->GetComponent<Component_EnemyShipController>()->Explode();

		// TODO: play some fancy animations or something before changing

		// SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level3>());

		this->reached_goal = true;
	}
}

void Scene_Level2::Unload() {
	LOG("LEVEL 2: Unloading level 2. Scene UUID: " + std::to_string(this->GetID()));

	this->StopAllSounds();
}

void Scene_Level2::SpawnAsteroid() {
	std::shared_ptr<GameObject> asteroid = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Asteroid, this->component_registry);

	// Randomize spawn position.
	float spawn_position_x = 0;
	float spawn_position_y = 0;
	if (rand() % 2 == 1) {
		spawn_position_x = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
		spawn_position_y = (float)(rand() % 2000 - 1000);
	}
	else {
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
	asteroid->GetComponent<Component_AsteroidController>()->rotation_direction = rand() % 2 == 1 ? CLOCKWISE : COUNTERCLOCKWISE;

	this->asteroids.push_back(asteroid);
}

void Scene_Level2::SpawnEnemyShip() {
	std::shared_ptr<GameObject> enemy_ship = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::EnemyShip, this->component_registry);
	
	// Randomize spawn position.
	float spawn_position_x = 0;
	float spawn_position_y = 0;
	if (rand() % 2 == 1) {
		spawn_position_x = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
		spawn_position_y = (float)(rand() % 2000 - 1000);
	}
	else {
		spawn_position_x = (float)(rand() % 2000 - 1000);
		spawn_position_y = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
	}
	enemy_ship->GetComponent<Component_Transform>()->position = Vector2D(spawn_position_x, spawn_position_y);
	
	enemy_ship->GetComponent<Component_EnemyShipController>()->player = this->player;
	this->enemy_ships.push_back(enemy_ship);
}