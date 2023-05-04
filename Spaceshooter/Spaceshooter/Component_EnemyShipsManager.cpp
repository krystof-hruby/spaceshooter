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
	if (this->score_manager.lock()->ReachedGoal())
		this->DespawnEnemyShips();

	this->grace_period_time += (float)Time::delta_time;
	this->enemy_ship_spawn_time += (float)Time::delta_time;

	if (!this->enemy_ships_despawned && this->grace_period_time > this->grace_period && this->enemy_ship_spawn_time > this->enemy_ship_spawn_period)
		this->SpawnEnemyShip();
}

void Component_EnemyShipsManager::SpawnEnemyShip() {
	std::shared_ptr<GameObject> enemy_ship = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::EnemyShip, this->GetGameObject()->GetComponentRegistry());
	enemy_ship->GetComponent<Component_EnemyShipController>()->player_transform = this->player_transform;
	enemy_ship->GetComponent<Component_EnemyShipController>()->score_manager = this->score_manager;

	// Add to scene.
	Scene::Instantiate(enemy_ship);
	this->enemy_ships.push_back(enemy_ship);

	// Reset spawning.
	this->enemy_ship_spawn_time = 0;
	this->enemy_ship_spawn_period = (float)((rand() % 10) + 1) / 5;
}

void Component_EnemyShipsManager::DespawnEnemyShips() {
	if (this->enemy_ships_despawned)
		return;
	
	for (auto enemy_ship : this->enemy_ships)
		if (!enemy_ship.expired() && enemy_ship.lock()->HasComponent<Component_EnemyShipController>())
			enemy_ship.lock()->GetComponent<Component_EnemyShipController>()->Explode();

	this->enemy_ships_despawned = true;
}
