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
	ScoreManager,
	Background,
	Player,
	PlayerBullet,
	Asteroid,
	AsteroidsManager,
	EnemyShip,
	EnemyShipsManager,
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
		{ GameObjectType::ScoreManager, CreateGameObject_ScoreManager },
		{ GameObjectType::Background, CreateGameObject_Background },
		{ GameObjectType::Player, CreateGameObject_Player },
		{ GameObjectType::PlayerBullet, CreateGameObject_PlayerBullet },
		{ GameObjectType::Asteroid, CreateGameObject_Asteroid },
		{ GameObjectType::AsteroidsManager, CreateGameObject_AsteroidsManager },
		{ GameObjectType::EnemyShip, CreateGameObject_EnemyShip },
		{ GameObjectType::EnemyShipsManager, CreateGameObject_EnemyShipsManager },
	};

	// Specific CreateGameObject methods:
	static std::shared_ptr<GameObject> CreateGameObject_Background(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_ScoreManager(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_Player(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_PlayerBullet(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_Asteroid(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_AsteroidsManager(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_EnemyShip(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_EnemyShipsManager(std::shared_ptr<ComponentRegistry> component_registry);

	// Applies prefab for this game object.
	std::shared_ptr<GameObject> ApplyPrefab(GameObjectType type, std::shared_ptr<GameObject> game_object);
	
	std::unordered_map<GameObjectType, std::function<std::shared_ptr<GameObject>(std::shared_ptr<GameObject>)>> prefabs_jump_table = {
		{ GameObjectType::Background, ApplyPrefab_Background },
		{ GameObjectType::Player, ApplyPrefab_Player },
		{ GameObjectType::PlayerBullet, ApplyPrefab_PlayerBullet },
		{ GameObjectType::Asteroid, ApplyPrefab_Asteroid },
		{ GameObjectType::EnemyShip, ApplyPrefab_EnemyShip },
	};

	// Specific ApplyPrefab methods:
	static std::shared_ptr<GameObject> ApplyPrefab_Background(std::shared_ptr<GameObject> game_object);
	static std::shared_ptr<GameObject> ApplyPrefab_Player(std::shared_ptr<GameObject> game_object);
	static std::shared_ptr<GameObject> ApplyPrefab_PlayerBullet(std::shared_ptr<GameObject> game_object);
	static std::shared_ptr<GameObject> ApplyPrefab_Asteroid(std::shared_ptr<GameObject> game_object);
	static std::shared_ptr<GameObject> ApplyPrefab_EnemyShip(std::shared_ptr<GameObject> game_object);

public:
	// Returns singleton instance.
	static GameObjectFactory& GetInstance();
	
	// Creates a game object based on the provided type by combining components.
	// Set apply_prefab to true to apply saved prefab for that game_object.
	std::shared_ptr<GameObject> CreateGameObject(GameObjectType type, std::shared_ptr<ComponentRegistry> component_registry, bool apply_prefab = false);
};

