// Scene_Level1.cpp
// Krystof Hruby
// 2023

#include "Scene_Level1.h"

#include "Logging.h"
#include "Time.h"

void Scene_Level1::Load() {
	LOG("LEVEL 1: Loading level 1. Scene UUID: " + std::to_string(this->GetID()));

	this->grace_period = 7;
	
	this->SetupBackground(L"assets/backgrounds/background_black.bmp");
	this->SetupPlayer();
}

void Scene_Level1::Update() {
	if (this->reached_goal)
		return;

	// Spawn asteroids after grace period.
	if (this->grace_period_time > this->grace_period)
		this->SpawnAsteroid(this->GetRandomSpawnPosition(), this->component_registry);

	this->grace_period_time += (float)Time::delta_time;

	// End game if reached goal.
	if (this->score_manager->score > this->goal) {
		this->DespawnAsteroids();

		// TODO: play some fancy animations or something before changing

		// SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level2>());
		this->reached_goal = true;
	}
}

void Scene_Level1::Unload() {
	LOG("LEVEL 1: Unloading level 1. Scene UUID: " + std::to_string(this->GetID()));

	this->StopAllSounds();
}

