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
	Player,
	PlayerBullet,
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
		{ GameObjectType::Player, CreateGameObject_Player },
		{ GameObjectType::PlayerBullet, CreateGameObject_PlayerBullet },
	};

	// Specific CreateGameObject functions:
	
	// Creates player spaceship.
	static std::shared_ptr<GameObject> CreateGameObject_Player(std::shared_ptr<ComponentRegistry> component_registry);
	
	// Creates a player bullet.
	static std::shared_ptr<GameObject> CreateGameObject_PlayerBullet(std::shared_ptr<ComponentRegistry> component_registry);

public:
	// Returns singleton instance.
	static GameObjectFactory& GetInstance();
	
	// Creates a game object based on the provided type by combining components.
	std::shared_ptr<GameObject> CreateGameObject(GameObjectType type, std::shared_ptr<ComponentRegistry> component_registry);
};

