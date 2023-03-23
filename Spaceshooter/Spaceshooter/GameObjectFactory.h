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
	Test,
	
	Blank,
};

// Creates specific game objects by combining components.
class GameObjectFactory final {
private:
	// Singleton
	GameObjectFactory() { }
	GameObjectFactory(GameObjectFactory const& copy) = delete;
	GameObjectFactory operator = (GameObjectFactory const& copy) = delete;
	
	std::unordered_map<GameObjectType, std::function<std::shared_ptr<GameObject>(std::shared_ptr<ComponentRegistry>)>> object_creation_jump_table = {
		{ GameObjectType::Test, CreateGameObject_Test },

		{ GameObjectType::Blank, CreateGameObject_Blank },
	};

	// Specific CreateGameObject functions:

	static std::shared_ptr<GameObject> CreateGameObject_Test(std::shared_ptr<ComponentRegistry> component_registry);
	
	// Creates a game object with Component_Transform only.
	static std::shared_ptr<GameObject> CreateGameObject_Blank(std::shared_ptr<ComponentRegistry> component_registry);
public:
	// Returns singleton instance.
	static GameObjectFactory& GetInstance();
	
	// Creates a game object based on the provided type by combining components.
	std::shared_ptr<GameObject> CreateGameObject(GameObjectType type, std::shared_ptr<ComponentRegistry> component_registry);
};

