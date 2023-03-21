// GameObjectFactory.h
// Krystof Hruby
// 2023

#include "GameObjectFactory.h"

#include "Component_Transform.h"
#include "Component_SpriteRenderer.h"
#include "Component_SoundEmitter.h"

GameObjectFactory& GameObjectFactory::GetInstance() {
	static GameObjectFactory instance;
	return instance;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject(GameObjectType type, std::shared_ptr<ComponentRegistry> component_registry) {
	return object_creation_jump_table[type](component_registry);
}

// GAME OBJECT CREATION FUNCTIONS:

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Test(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = GameObjectFactory::CreateGameObject_Blank(component_registry);
	game_object->AddComponent<Component_SpriteRenderer>(std::make_shared<Component_SpriteRenderer>(game_object, L"assets/test.bmp"));
	game_object->AddComponent<Component_InputReader>(std::make_shared<Component_InputReader>(game_object));
	std::vector<Sound> sounds = { L"assets/test.wav" };
	game_object->AddComponent<Component_SoundEmitter>(std::make_shared<Component_SoundEmitter>(game_object, sounds));
	return game_object;
}


std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Blank(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->AddComponent<Component_Transform>(std::make_shared<Component_Transform>(game_object));
	return game_object;
}