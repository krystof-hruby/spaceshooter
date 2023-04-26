// AsteroidsManager.cpp
// Krystof Hruby
// 2023


#include "AsteroidsManager.h"

#include "Component_AsteroidCollider.h"
#include "Component_AsteroidController.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"
#include "GameObjectFactory.h"
#include "Time.h"

void AsteroidsManager::SpawnAsteroid(Vector2D spawn_position, std::shared_ptr<ComponentRegistry> component_registry) {
	this->asteroid_spawn_time += (float)Time::delta_time;

	if (!(this->asteroid_spawn_time > this->asteroid_spawn_period))
		return;


	std::shared_ptr<GameObject> asteroid = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Asteroid, component_registry);

	// Randomize spawn position.
	asteroid->GetComponent<Component_Transform>()->position = spawn_position;

	// Randomize sprite.
	Sprite sprite = rand() % 2 == 1 ? L"assets/asteroids/asteroid_large.bmp" : L"assets/asteroids/asteroid_small.bmp";
	asteroid->GetComponent<Component_SpriteRenderer>()->SetSprite(sprite);

	// Randomize scale.
	asteroid->GetComponent<Component_Transform>()->scale = ((float)((rand() % 3) + 2) / 10);
	int scale_multiplier = sprite == L"assets/asteroids/asteroid_large.bmp" ? 190 : 250; // Sprites have different sizes.
	asteroid->GetComponent<Component_AsteroidCollider>()->radius = asteroid->GetComponent<Component_Transform>()->scale * scale_multiplier;

	// Randomize values.
	Vector2D movement_direction;
	movement_direction.XValue = spawn_position.XValue < 0 ? (float)(rand() % 10) : -(float)(rand() % 10);
	movement_direction.YValue = spawn_position.YValue < 0 ? (float)(rand() % 10) : -(float)(rand() % 10);
	asteroid->GetComponent<Component_AsteroidController>()->movement_direction = movement_direction;
	asteroid->GetComponent<Component_AsteroidController>()->movement_speed = (float)(rand() % 100);
	asteroid->GetComponent<Component_AsteroidController>()->rotation_speed = (float)(rand() % 5 + 1);
	asteroid->GetComponent<Component_AsteroidController>()->rotation_direction = rand() % 2 == 1 ? CLOCKWISE : COUNTERCLOCKWISE;


	this->asteroids.push_back(asteroid);
	this->asteroid_spawn_time = 0;
	this->asteroid_spawn_period = (float)((rand() % 10) + 1) / 9; // Randomize spawn period.
}

void AsteroidsManager::DespawnAsteroids() {
	for (auto asteroid : this->asteroids)
		if (asteroid->HasComponent<Component_AsteroidController>())
			asteroid->GetComponent<Component_AsteroidController>()->Explode();
}
