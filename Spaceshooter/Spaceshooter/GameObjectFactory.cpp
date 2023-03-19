// GameObjectFactory.h
// Krystof Hruby
// 2023

#include "GameObjectFactory.h"

#include <exception>

#include "Component_Transform.h"

// Returns singleton instance.
GameObjectFactory& GameObjectFactory::GetInstance() {
	static GameObjectFactory instance;
	return instance;
}

// Creates a game object based on the provided type by combining components.
std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject(GameObjectType type, std::shared_ptr<ComponentRegistry> component_registry) {
	return object_creation_jump_table[type](component_registry);
}

// GAME OBJECT CREATION FUNCTIONS:

// Creates a blank game object => only transform component.
std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Blank(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->AddComponent<Component_Transform>(std::make_shared<Component_Transform>(game_object));
	return game_object;
}