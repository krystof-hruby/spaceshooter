// GameObjectFactory.h
// Krystof Hruby
// 2023

#include "GameObjectFactory.h"

#include "Component_Test.h"

#include "Component_Animator.h"
#include "Component_AudioEmitter.h"
#include "Component_CircleCollider.h"
#include "Component_InputReader.h"
#include "Component_PlayerBulletController.h"
#include "Component_PlayerController.h"
#include "Component_PlayerInput.h"
#include "Component_RectangleCollider.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"

GameObjectFactory& GameObjectFactory::GetInstance() {
	static GameObjectFactory instance;
	return instance;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject(GameObjectType type, std::shared_ptr<ComponentRegistry> component_registry) {
	return object_creation_jump_table[type](component_registry);
}


// Specific CreateGameObject functions:

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Player(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->AddComponent<Component_Transform>();
	game_object->AddComponent<Component_CircleCollider>();
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->AddComponent<Component_AudioEmitter>();
	
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/test.bmp");

	game_object->AddComponent<Component_PlayerInput>();
	game_object->AddComponent<Component_PlayerController>();

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_PlayerBullet(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->AddComponent<Component_Transform>();
	game_object->AddComponent<Component_RectangleCollider>();
	game_object->AddComponent<Component_SpriteRenderer>();
	
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/test.bmp");

	game_object->AddComponent<Component_PlayerBulletController>();

	return game_object;
}
