// GameObjectFactory.h
// Krystof Hruby
// 2023

#include "GameObjectFactory.h"

#include "Component_Test.h"

#include "Component_Animator.h"
#include "Component_AsteroidCollider.h"
#include "Component_AsteroidController.h"
#include "Component_AudioEmitter.h"
#include "Component_CircleCollider.h"
#include "Component_EnemyShipCollider.h"
#include "Component_EnemyShipController.h"
#include "Component_InputReader.h"
#include "Component_PlayerBulletCollider.h"
#include "Component_PlayerBulletController.h"
#include "Component_PlayerCollider.h"
#include "Component_PlayerController.h"
#include "Component_PlayerInput.h"
#include "Component_RectangleCollider.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"
#include "Global.h"

GameObjectFactory& GameObjectFactory::GetInstance() {
	static GameObjectFactory instance;
	return instance;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject(GameObjectType type, std::shared_ptr<ComponentRegistry> component_registry) {
	return object_creation_jump_table[type](component_registry);
}


// Specific CreateGameObject functions:

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Background(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Background";

	game_object->AddComponent<Component_Transform>();
	game_object->GetComponent<Component_Transform>()->rotation = PI / 2;

	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/backgrounds/background_black.bmp");

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Player(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Player";

	game_object->AddComponent<Component_Transform>();
	game_object->GetComponent<Component_Transform>()->scale = 0.2f;
	
	game_object->AddComponent<Component_PlayerCollider>();
	game_object->GetComponent<Component_PlayerCollider>()->radius = 45;
	
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/spaceships/spaceship_green.bmp");
	
	game_object->AddComponent<Component_Animator>();
	std::vector<Sprite> sprites = {
		L"assets/spaceships/blue_ship_explosion_1.bmp",
		L"assets/spaceships/blue_ship_explosion_2.bmp",
		L"assets/spaceships/blue_ship_explosion_3.bmp",
		L"assets/spaceships/blue_ship_explosion_4.bmp",
	};
	std::shared_ptr<Animation> animation = std::make_shared<Animation>("player explode", sprites, false, 15);
	game_object->GetComponent<Component_Animator>()->RegisterAnimation(animation);

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
	game_object->tag = "Player Bullet";

	game_object->AddComponent<Component_Transform>();
	game_object->GetComponent<Component_Transform>()->scale = 0.2f;
	
	game_object->AddComponent<Component_PlayerBulletCollider>();
	game_object->GetComponent<Component_PlayerBulletCollider>()->width = 80;
	game_object->GetComponent<Component_PlayerBulletCollider>()->height = 40;
	
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/projectiles/projectile_pink.bmp");
	
	game_object->AddComponent<Component_PlayerBulletController>();
	game_object->GetComponent<Component_PlayerBulletController>()->movement_speed = 1500;
	
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Asteroid(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Asteroid";

	game_object->AddComponent<Component_Transform>();
	
	game_object->AddComponent<Component_AsteroidCollider>();
	
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/asteroids/asteroid_large.bmp");
	
	game_object->AddComponent<Component_Animator>();
	std::vector<Sprite> sprites = {
		L"assets/asteroids/asteroid_explosion_1.bmp",
		L"assets/asteroids/asteroid_explosion_2.bmp",
		L"assets/asteroids/asteroid_explosion_3.bmp",
		L"assets/asteroids/asteroid_explosion_4.bmp",
	};
	std::shared_ptr<Animation> animation = std::make_shared<Animation>("asteroid explosion", sprites, false, 15);
	game_object->GetComponent<Component_Animator>()->RegisterAnimation(animation);

	game_object->AddComponent<Component_AsteroidController>();

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_EnemyShip(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Enemy Ship";

	game_object->AddComponent<Component_Transform>();
	game_object->GetComponent<Component_Transform>()->scale = 0.2f;

	game_object->AddComponent<Component_EnemyShipCollider>();
	game_object->GetComponent<Component_EnemyShipCollider>()->radius = 50;

	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/spaceships/spaceship_purple.bmp");

	game_object->AddComponent<Component_Animator>();
	std::vector<Sprite> sprites = {
		L"assets/spaceships/purple_ship_explosion_1.bmp",
		L"assets/spaceships/purple_ship_explosion_2.bmp",
		L"assets/spaceships/purple_ship_explosion_3.bmp",
		L"assets/spaceships/purple_ship_explosion_4.bmp",
	};
	std::shared_ptr<Animation> animation = std::make_shared<Animation>("enemy ship explosion", sprites, false, 15);
	game_object->GetComponent<Component_Animator>()->RegisterAnimation(animation);

	game_object->AddComponent<Component_EnemyShipController>();
	game_object->GetComponent<Component_EnemyShipController>()->movement_speed = 0.8f;

	return game_object;
}
