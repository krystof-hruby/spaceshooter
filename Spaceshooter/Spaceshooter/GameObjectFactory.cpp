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
	game_object->GetComponent<Component_Transform>()->scale = 0.15f;
	
	game_object->AddComponent<Component_CircleCollider>();
	game_object->GetComponent<Component_CircleCollider>()->radius = 30;
	
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/player/player_spaceship.bmp");
	
	game_object->AddComponent<Component_AudioEmitter>();
	
	game_object->AddComponent<Component_PlayerInput>();
	
	game_object->AddComponent<Component_PlayerController>();
	game_object->GetComponent<Component_PlayerController>()->canon_offset = Vector2D(0, 100);
	game_object->GetComponent<Component_PlayerController>()->movement_speed = 500;
	game_object->GetComponent<Component_PlayerController>()->rotation_speed = 5;
	game_object->GetComponent<Component_PlayerController>()->reload_period = 0.25f;
	
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_PlayerBullet(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	
	game_object->AddComponent<Component_Transform>();
	game_object->GetComponent<Component_Transform>()->scale = 0.1f;
	
	game_object->AddComponent<Component_RectangleCollider>();
	game_object->GetComponent<Component_RectangleCollider>()->width = 15;
	game_object->GetComponent<Component_RectangleCollider>()->height = 55;
	
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/player/player_bullet.bmp");
	
	game_object->AddComponent<Component_PlayerBulletController>();
	game_object->GetComponent<Component_PlayerBulletController>()->movement_speed = 800;
	
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Asteroid(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	
	game_object->AddComponent<Component_Transform>();
	
	game_object->AddComponent<Component_CircleCollider>();
	
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/asteroids/asteroid1.bmp");
	
	game_object->AddComponent<Component_Animator>();
	std::vector<Sprite> sprites = {L"assets/asteroids/asteroid1.bmp"/*TODO: add frames*/};
	std::shared_ptr<Animation> animation = std::make_shared<Animation>("asteroid explosion", sprites);
	game_object->GetComponent<Component_Animator>()->RegisterAnimation(animation);

	game_object->AddComponent<Component_AsteroidController>();

	return game_object;
}
