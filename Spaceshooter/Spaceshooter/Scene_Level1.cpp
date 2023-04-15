// Scene_Level1.cpp
// Krystof Hruby
// 2023

#include "Scene_Level1.h"

#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Logging.h"
#include "SceneManager.h"
#include "Scene_Level2.h"
#include "Component_AsteroidController.h"
#include "Component_CircleCollider.h"
#include "Component_RectangleCollider.h"
#include "Component_Transform.h"

void Scene_Level1::SpawnAsteroid() {
	std::shared_ptr<GameObject> asteroid = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Asteroid, this->component_registry);
	
	asteroid->GetComponent<Component_Transform>()->position = Vector2D((float)(rand() % 100 - 50), (float)(rand() % 100 - 50));
	
	asteroid->GetComponent<Component_CircleCollider>()->radius = (float)(rand() % 50 + 50);

	asteroid->GetComponent<Component_AsteroidController>()->movement_direction = Vector2D((float)(rand() % 100 - 50), (float)(rand() % 100 - 50));
	asteroid->GetComponent<Component_AsteroidController>()->movement_speed = (float)(rand() % 20);
	asteroid->GetComponent<Component_AsteroidController>()->rotation_speed = (float)(rand() % 20);
	if (rand() % 2 == 1)
		asteroid->GetComponent<Component_AsteroidController>()->rotation_direction = CLOCKWISE;
	else
		asteroid->GetComponent<Component_AsteroidController>()->rotation_direction = COUNTERCLOCKWISE;

	
	this->asteroids.push_back(asteroid);
}

void Scene_Level1::Load() {
	LOG("LEVEL 1: Loading level 1. Scene UUID: " + std::to_string(this->GetID()));

	this->player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, this->component_registry);
}

void Scene_Level1::Update() {
	if (this->asteroid_spawn_time > this->asteroid_spawn_period) {
		SpawnAsteroid();
		this->asteroid_spawn_time = 0;
		this->asteroid_spawn_period = (float)(rand() % 5 + 1); // Randomize spawn period.
	}

	this->asteroid_spawn_time += (float)Time::delta_time;
}

void Scene_Level1::Unload() {
	LOG("LEVEL 1: Unloading level 1. Scene UUID: " + std::to_string(this->GetID()));

	this->StopAllSounds();
}
