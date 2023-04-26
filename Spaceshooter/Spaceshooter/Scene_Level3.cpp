// Scene_Level3.cpp
// Krystof Hruby
// 2023

#include "Scene_Level3.h"

#include "Logging.h"
#include "Time.h"

void Scene_Level3::Load() {
	LOG("LEVEL 3: Loading level 3. Scene UUID: " + std::to_string(this->GetID()));

	this->grace_period = 7;
	this->SetupBackground(L"assets/backgrounds/background_purple.bmp");
	this->SetupPlayer();
}

void Scene_Level3::Update() {
	if (this->reached_goal)
		return;

	this->grace_period_time += (float)Time::delta_time;

	// Spawn asteroids after grace period.
	if (this->grace_period_time > this->grace_period)
		this->SpawnAsteroid(this->GetRandomSpawnPosition(), this->component_registry);

	// Spawn enemy ships after grace period.
	if (this->grace_period_time > this->grace_period)
		this->SpawnEnemyShip(this->GetRandomSpawnPosition(), this->player, this->component_registry);

	// End round when reached score.
	if (this->score_manager->score > this->goal) {
		this->DespawnAsteroids();
		this->DespawnEnemyShips();

		// TODO: play some fancy animations or something before changing

		// SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level3>());

		this->reached_goal = true;
	}
}

void Scene_Level3::Unload() {
	LOG("LEVEL 3: Unloading level 3. Scene UUID: " + std::to_string(this->GetID()));

	this->StopAllSounds();
}
