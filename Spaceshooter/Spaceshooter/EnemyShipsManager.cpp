// EnemyShipsManager.cpp
// Krystof Hruby
// 2023

#include "EnemyShipsManager.h"

#include "Component_EnemyShipController.h"
#include "Component_Transform.h"
#include "GameObjectFactory.h"
#include "Time.h"

void EnemyShipsManager::SpawnEnemyShip(Vector2D spawn_position, std::shared_ptr<GameObject> player, std::shared_ptr<ComponentRegistry> component_registry) {
	this->enemy_ship_spawn_time += (float)Time::delta_time;
	
	if (!(this->enemy_ship_spawn_time > this->enemy_ship_spawn_period))
		return;


	std::shared_ptr<GameObject> enemy_ship = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::EnemyShip, component_registry);
	enemy_ship->GetComponent<Component_Transform>()->position = spawn_position;
	enemy_ship->GetComponent<Component_EnemyShipController>()->player = player;


	this->enemy_ships.push_back(enemy_ship);
	this->enemy_ship_spawn_time = 0;
	this->enemy_ship_spawn_period = (float)((rand() % 10) + 1) / 5;
}

void EnemyShipsManager::DespawnEnemyShips() {
	for (auto enemy_ship : this->enemy_ships)
		if (enemy_ship->HasComponent<Component_EnemyShipController>())
			enemy_ship->GetComponent<Component_EnemyShipController>()->Explode();
}
