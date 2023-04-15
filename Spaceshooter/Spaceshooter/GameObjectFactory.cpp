// GameObjectFactory.h
// Krystof Hruby
// 2023

#include "GameObjectFactory.h"

#include "Component_Test.h"

#include "Component_Animator.h"
#include "Component_AsteroidController.h"
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
	game_object->GetComponent<Component_CircleCollider>()->radius = 100;
	
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/test.bmp");
	
	game_object->AddComponent<Component_AudioEmitter>();
	
	game_object->AddComponent<Component_PlayerInput>();
	
	game_object->AddComponent<Component_PlayerController>();
	game_object->GetComponent<Component_PlayerController>()->movement_speed = 500;
	game_object->GetComponent<Component_PlayerController>()->rotation_speed = 5;
	game_object->GetComponent<Component_PlayerController>()->reload_period = 1;
	
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_PlayerBullet(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	
	game_object->AddComponent<Component_Transform>();
	
	game_object->AddComponent<Component_RectangleCollider>();
	game_object->GetComponent<Component_RectangleCollider>()->width = 100;
	game_object->GetComponent<Component_RectangleCollider>()->height = 100;
	
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/test.bmp");
	
	game_object->AddComponent<Component_PlayerBulletController>();
	game_object->GetComponent<Component_PlayerBulletController>()->movement_speed = 500;
	
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Asteroid(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	
	game_object->AddComponent<Component_Transform>();
	
	game_object->AddComponent<Component_CircleCollider>();
	
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/test.bmp");
	
	game_object->AddComponent<Component_AsteroidController>();

	return game_object;
}
