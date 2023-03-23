// GameObjectFactory.h
// Krystof Hruby
// 2023

#include "GameObjectFactory.h"

#include "Component_Transform.h"
#include "Component_SpriteRenderer.h"
#include "Component_AudioEmitter.h"
#include "Component_RectangleCollider.h"

GameObjectFactory& GameObjectFactory::GetInstance() {
	static GameObjectFactory instance;
	return instance;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject(GameObjectType type, std::shared_ptr<ComponentRegistry> component_registry) {
	return object_creation_jump_table[type](component_registry);
}

// Specific CreateGameObject functions:

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Test(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = GameObjectFactory::CreateGameObject_Blank(component_registry);
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->GetComponent<Component_SpriteRenderer>();
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/test.bmp");
	game_object->AddComponent<Component_AudioEmitter>();
	game_object->GetComponent<Component_AudioEmitter>()->Load(L"assets/test.wav");
	game_object->AddComponent<Component_RectangleCollider>();
	return game_object;
}


std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Blank(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->AddComponent<Component_Transform>();
	return game_object;
}