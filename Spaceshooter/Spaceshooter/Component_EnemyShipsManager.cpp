// Component_EnemyShipsManager.cpp
// Krystof Hruby
// 2023

#include "Component_EnemyShipsManager.h"

#include "Component_EnemyShipController.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Scene.h"
#include "Time.h"

void Component_EnemyShipsManager::Update() {
	this->grace_period_time += (float)Time::delta_time;
	this->enemy_ship_spawn_time += (float)Time::delta_time;

	if (!this->enemy_ships_despawned && this->grace_period_time > this->grace_period && this->enemy_ship_spawn_time > this->enemy_ship_spawn_period)
		this->SpawnEnemyShip();
}

void Component_EnemyShipsManager::SpawnEnemyShip() {
	std::shared_ptr<GameObject> enemy_ship = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::EnemyShip, this->GetGameObject()->GetComponentRegistry());
	enemy_ship->GetComponent<Component_EnemyShipController>()->player_transform = this->player_transform;

	// Add to scene.
	Scene::Instantiate(enemy_ship);

	// Reset spawning.
	this->enemy_ship_spawn_time = 0;
	this->enemy_ship_spawn_period = (float)((rand() % 10) + 1) / 5;
}
