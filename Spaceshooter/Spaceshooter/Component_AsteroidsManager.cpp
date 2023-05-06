// Component_AsteroidsManager.cpp
// Krystof Hruby
// 2023

#include "Component_AsteroidsManager.h"

#include "AudioClips.h"
#include "Component_AsteroidCollider.h"
#include "Component_AsteroidController.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Scene.h"
#include "Time.h"

void Component_AsteroidsManager::Update() {
	this->asteroid_spawn_time += (float)Time::delta_time;

	if (this->asteroid_spawn_time > this->asteroid_spawn_period)
		this->SpawnAsteroid();
}

void Component_AsteroidsManager::SpawnAsteroid() {
	std::shared_ptr<GameObject> asteroid = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Asteroid, this->GetGameObject()->GetComponentRegistry());
	Scene::Instantiate(asteroid);

	// Reset spawning.
	this->asteroid_spawn_time = 0;
	this->asteroid_spawn_period = (float)((rand() % 10) + 1) / 15; // Randomize spawn period.
}

