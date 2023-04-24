// GameObjectFactory.h
// Krystof Hruby
// 2023

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "ComponentRegistry.h"
#include "GameObject.h"

// Type of game object based on which GameObjectFactory creates game objects.
enum class GameObjectType {
	Background,
	Player,
	PlayerBullet,
	Asteroid,
	EnemyShip,
};

// Creates specific game objects by combining components.
class GameObjectFactory final {
private:
	// Singleton
	GameObjectFactory() { }
	GameObjectFactory(GameObjectFactory const& copy) = delete;
	GameObjectFactory operator = (GameObjectFactory const& copy) = delete;
	
	// Add all specific objects with their creation functions here:
	std::unordered_map<GameObjectType, std::function<std::shared_ptr<GameObject>(std::shared_ptr<ComponentRegistry>)>> object_creation_jump_table = {
		{ GameObjectType::Background, CreateGameObject_Background },
		{ GameObjectType::Player, CreateGameObject_Player },
		{ GameObjectType::PlayerBullet, CreateGameObject_PlayerBullet },
		{ GameObjectType::Asteroid, CreateGameObject_Asteroid },
		{ GameObjectType::EnemyShip, CreateGameObject_EnemyShip },
	};

	// Specific CreateGameObject functions:
	
	// Creates game scene background.
	static std::shared_ptr<GameObject> CreateGameObject_Background(std::shared_ptr<ComponentRegistry> component_registry);
	
	// Creates player spaceship.
	static std::shared_ptr<GameObject> CreateGameObject_Player(std::shared_ptr<ComponentRegistry> component_registry);
	
	// Creates a player bullet.
	static std::shared_ptr<GameObject> CreateGameObject_PlayerBullet(std::shared_ptr<ComponentRegistry> component_registry);

	// Creates an asteroid.
	static std::shared_ptr<GameObject> CreateGameObject_Asteroid(std::shared_ptr<ComponentRegistry> component_registry);

	// Creates enemy ship.
	static std::shared_ptr<GameObject> CreateGameObject_EnemyShip(std::shared_ptr<ComponentRegistry> component_registry);

public:
	// Returns singleton instance.
	static GameObjectFactory& GetInstance();
	
	// Creates a game object based on the provided type by combining components.
	std::shared_ptr<GameObject> CreateGameObject(GameObjectType type, std::shared_ptr<ComponentRegistry> component_registry);
};

