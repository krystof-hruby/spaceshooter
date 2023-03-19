// GameObjectFactory.h
// Krystof Hruby
// 2023

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "GameObject.h"
#include "ComponentRegistry.h"

enum class GameObjectType {
	Blank,
};

// Creates specific game objects by combining components.
class GameObjectFactory {
private:
	GameObjectFactory() { }
	GameObjectFactory(GameObjectFactory const& copy) = delete;
	GameObjectFactory operator = (GameObjectFactory const& copy) = delete;
	
	std::unordered_map<GameObjectType, std::function<std::shared_ptr<GameObject>(std::shared_ptr<ComponentRegistry>)>> object_creation_jump_table = {
		{ GameObjectType::Blank, CreateGameObject_Blank },
	};

	// GAME OBJECT CREATION FUNCTIONS:

	static std::shared_ptr<GameObject> CreateGameObject_Blank(std::shared_ptr<ComponentRegistry> component_registry);
public:
	static GameObjectFactory& GetInstance();
	
	std::shared_ptr<GameObject> CreateGameObject(GameObjectType type, std::shared_ptr<ComponentRegistry> component_registry);
};

