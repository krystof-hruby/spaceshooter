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
	if (this->score_manager.lock()->ReachedGoal())
		this->DespawnAsteroids();

	this->grace_period_time += (float)Time::delta_time;
	this->asteroid_spawn_time += (float)Time::delta_time;

	if (!this->asteroids_despawned && this->grace_period_time > this->grace_period && this->asteroid_spawn_time > this->asteroid_spawn_period)
		this->SpawnAsteroid();
}

void Component_AsteroidsManager::SpawnAsteroid() {
	std::shared_ptr<GameObject> asteroid = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Asteroid, this->GetGameObject()->GetComponentRegistry());
	asteroid->GetComponent<Component_AsteroidController>()->score_manager = this->score_manager;

	// Add to scene.
	Scene::Instantiate(asteroid);
	this->asteroids.push_back(asteroid);

	// Reset spawning.
	this->asteroid_spawn_time = 0;
	this->asteroid_spawn_period = (float)((rand() % 10) + 1) / 15; // Randomize spawn period.
}

void Component_AsteroidsManager::DespawnAsteroids() {
	if (this->asteroids_despawned)
		return;

	for (auto asteroid : this->asteroids)
		if (!asteroid.expired() && asteroid.lock()->HasComponent<Component_AsteroidController>())
			asteroid.lock()->GetComponent<Component_AsteroidController>()->Explode();

	this->asteroids_despawned = true;
}
