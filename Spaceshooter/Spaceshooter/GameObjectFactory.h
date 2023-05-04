// GameObjectFactory.h
// Krystof Hruby
// 2023

#pragma once

#include <functional>
#include "GameObject.h"

// Type of game object based on which GameObjectFactory creates game objects.
enum class GameObjectType {
	Level1Manager,
	Level2Manager,
	Level3Manager,
	Background,
	Player,
	PlayerBullet,
	Asteroid,
	AsteroidsManager,
	EnemyShip,
	EnemyShipsManager,
	Boss,
	HomingMissile,
	Mine,
};

// Creates specific game objects by combining components.
class GameObjectFactory final {
public:
	// Returns singleton instance.
	static GameObjectFactory& GetInstance();
	
	// Creates a game object based on the provided type by combining components.
	// Set apply_prefab to true to apply saved prefab for that game_object.
	std::shared_ptr<GameObject> CreateGameObject(GameObjectType type, std::shared_ptr<ComponentRegistry> component_registry);

private:
	// Singleton.
	GameObjectFactory() { }
	GameObjectFactory(GameObjectFactory const& copy) = delete;
	GameObjectFactory operator = (GameObjectFactory const& copy) = delete;

	// Add all specific objects with their creation functions here:
	std::unordered_map<GameObjectType, std::function<std::shared_ptr<GameObject>(std::shared_ptr<ComponentRegistry>)>> object_creation_jump_table = {
		{ GameObjectType::Level1Manager, CreateGameObject_Level1Manager },
		{ GameObjectType::Level2Manager, CreateGameObject_Level2Manager },
		{ GameObjectType::Level3Manager, CreateGameObject_Level3Manager },
		{ GameObjectType::Background, CreateGameObject_Background },
		{ GameObjectType::Player, CreateGameObject_Player },
		{ GameObjectType::PlayerBullet, CreateGameObject_PlayerBullet },
		{ GameObjectType::Asteroid, CreateGameObject_Asteroid },
		{ GameObjectType::AsteroidsManager, CreateGameObject_AsteroidsManager },
		{ GameObjectType::EnemyShip, CreateGameObject_EnemyShip },
		{ GameObjectType::EnemyShipsManager, CreateGameObject_EnemyShipsManager },
		{ GameObjectType::Boss, CreateGameObject_Boss },
		{ GameObjectType::HomingMissile, CreateGameObject_HomingMissile },
		{ GameObjectType::Mine, CreateGameObject_Mine },
	};

	// Specific CreateGameObject methods:
	static std::shared_ptr<GameObject> CreateGameObject_Level1Manager(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_Level2Manager(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_Level3Manager(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_Background(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_Player(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_PlayerBullet(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_Asteroid(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_AsteroidsManager(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_EnemyShip(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_EnemyShipsManager(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_Boss(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_HomingMissile(std::shared_ptr<ComponentRegistry> component_registry);
	static std::shared_ptr<GameObject> CreateGameObject_Mine(std::shared_ptr<ComponentRegistry> component_registry);
};

