// GameObjectFactory.h
// Krystof Hruby
// 2023

#include "GameObjectFactory.h"

#include "Component_Animator.h"
#include "Component_AsteroidCollider.h"
#include "Component_AsteroidController.h"
#include "Component_AsteroidsManager.h"
#include "Component_AudioEmitter.h"
#include "Component_BossCollider.h"
#include "Component_BossController.h"
#include "Component_CircleCollider.h"
#include "Component_EnemyShipCollider.h"
#include "Component_EnemyShipController.h"
#include "Component_EnemyShipsManager.h"
#include "Component_HomingMissileController.h"
#include "Component_InputReader.h"
#include "Component_PlayerBulletCollider.h"
#include "Component_PlayerBulletController.h"
#include "Component_PlayerCollider.h"
#include "Component_PlayerController.h"
#include "Component_PlayerInput.h"
#include "Component_RectangleCollider.h"
#include "Component_ScoreManager.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"
#include "Constants.h"
#include "Debugging.h"
#include "Logging.h" // TODO: remove

GameObjectFactory& GameObjectFactory::GetInstance() {
	static GameObjectFactory instance;
	return instance;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject(GameObjectType type, std::shared_ptr<ComponentRegistry> component_registry, bool apply_prefab) {
	if (apply_prefab)
		return this->ApplyPrefab(type, object_creation_jump_table[type](component_registry));
	else
		return object_creation_jump_table[type](component_registry);
}

std::shared_ptr<GameObject> GameObjectFactory::ApplyPrefab(GameObjectType type, std::shared_ptr<GameObject> game_object) {
	return this->prefabs_jump_table[type](game_object);
}


// Specific CreateGameObject methods:

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Background(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Background";
	game_object->AddComponent<Component_Transform>();
	game_object->AddComponent<Component_SpriteRenderer>();
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_ScoreManager(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Score Manager";
	game_object->AddComponent<Component_ScoreManager>();
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Player(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Player";
	game_object->AddComponent<Component_Transform>();
	game_object->AddComponent<Component_PlayerCollider>();
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->AddComponent<Component_Animator>();
	game_object->AddComponent<Component_AudioEmitter>();
	game_object->AddComponent<Component_PlayerInput>();
	game_object->AddComponent<Component_PlayerController>();	
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_PlayerBullet(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Player Bullet";
	game_object->AddComponent<Component_Transform>();
	game_object->AddComponent<Component_PlayerBulletCollider>();
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->AddComponent<Component_PlayerBulletController>();
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Asteroid(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Asteroid";
	game_object->AddComponent<Component_Transform>();
	game_object->AddComponent<Component_AsteroidCollider>();
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->AddComponent<Component_Animator>();
	game_object->AddComponent<Component_AsteroidController>();
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_AsteroidsManager(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Asteroids Manager";
	game_object->AddComponent<Component_AsteroidsManager>();
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_EnemyShip(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Enemy Ship";
	game_object->AddComponent<Component_Transform>();
	game_object->AddComponent<Component_EnemyShipCollider>();
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->AddComponent<Component_Animator>();
	game_object->AddComponent<Component_EnemyShipController>();
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_EnemyShipsManager(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Enemy Ships Manager";
	game_object->AddComponent<Component_EnemyShipsManager>();
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Boss(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Boss";
	game_object->AddComponent<Component_Transform>();
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->AddComponent<Component_Animator>();
	game_object->AddComponent<Component_BossCollider>();
	game_object->AddComponent<Component_BossController>();
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_HomingMissile(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Homing Missile";
	game_object->AddComponent<Component_Transform>();
	game_object->AddComponent<Component_SpriteRenderer>();
	game_object->AddComponent<Component_Animator>();
	game_object->AddComponent<Component_HomingMissileController>();
	return game_object;
}


// Specific ApplyPrefab methods:

std::shared_ptr<GameObject> GameObjectFactory::ApplyPrefab_Background(std::shared_ptr<GameObject> game_object) {
	game_object->GetComponent<Component_Transform>()->rotation = PI / 2;

	#if VISUALIZE_HITBOXES
		game_object->GetComponent<Component_SpriteRenderer>()->is_active = false;
	#endif

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::ApplyPrefab_Player(std::shared_ptr<GameObject> game_object) {
	auto transform = game_object->GetComponent<Component_Transform>();
	auto sprite_renderer = game_object->GetComponent<Component_SpriteRenderer>();
	auto animator = game_object->GetComponent<Component_Animator>();
	auto collider = game_object->GetComponent<Component_PlayerCollider>();
	auto player_controller = game_object->GetComponent<Component_PlayerController>();

	transform->scale = 0.2f;
	collider->radius = 45;
	sprite_renderer->SetSprite(L"assets/spaceships/spaceship_green.png");
	
	std::vector<Sprite> sprites = {
		L"assets/spaceships/blue_ship_explosion_1.png",
		L"assets/spaceships/blue_ship_explosion_2.png",
		L"assets/spaceships/blue_ship_explosion_3.png",
		L"assets/spaceships/blue_ship_explosion_4.png",
	};
	std::shared_ptr<Animation> animation = std::make_shared<Animation>("player explode", sprites, false, 15);
	animator->RegisterAnimation(animation);
	sprites = {
		L"assets/spaceships/blue_ship_spawn_1.png",
		L"assets/spaceships/blue_ship_spawn_2.png",
		L"assets/spaceships/blue_ship_spawn_3.png",
		L"assets/spaceships/blue_ship_spawn_4.png",
	};
	animation = std::make_shared<Animation>("player spawn", sprites, false, 11);
	animator->RegisterAnimation(animation);
	
	player_controller->canon_offset = Vector2D(0, 100);
	player_controller->movement_speed = 500;
	player_controller->rotation_speed = 5;
	player_controller->reload_period = 0.25f;

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::ApplyPrefab_PlayerBullet(std::shared_ptr<GameObject> game_object) {
	game_object->GetComponent<Component_Transform>()->scale = 0.2f;
	game_object->GetComponent<Component_PlayerBulletCollider>()->width = 80;
	game_object->GetComponent<Component_PlayerBulletCollider>()->height = 40;
	game_object->GetComponent<Component_SpriteRenderer>()->SetSprite(L"assets/projectiles/projectile_pink.png");
	game_object->GetComponent<Component_PlayerBulletController>()->movement_speed = 1500;

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::ApplyPrefab_Asteroid(std::shared_ptr<GameObject> game_object) {
	auto transform = game_object->GetComponent<Component_Transform>();
	auto sprite_renderer = game_object->GetComponent<Component_SpriteRenderer>();
	auto collider = game_object->GetComponent<Component_AsteroidCollider>();
	auto asteroid_controller = game_object->GetComponent<Component_AsteroidController>();

	// Randomize spawn position.
	if (rand() % 2 == 1) {
		transform->position.XValue = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
		transform->position.YValue = (float)(rand() % 2000 - 1000);
	} else {
		transform->position.XValue = (float)(rand() % 2000 - 1000);
		transform->position.YValue = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
	}

	// Add animation.
	std::vector<Sprite> sprites = {
		L"assets/asteroids/asteroid_explosion_1.png",
		L"assets/asteroids/asteroid_explosion_2.png",
		L"assets/asteroids/asteroid_explosion_3.png",
		L"assets/asteroids/asteroid_explosion_4.png",
	};
	std::shared_ptr<Animation> animation = std::make_shared<Animation>("asteroid explosion", sprites, false, 15);
	game_object->GetComponent<Component_Animator>()->RegisterAnimation(animation);

	// Randomize sprite.
	Sprite sprite = rand() % 2 == 1 ? L"assets/asteroids/asteroid_large.png" : L"assets/asteroids/asteroid_small.png";
	sprite_renderer->SetSprite(sprite);

	// Randomize scale.
	transform->scale = ((float)((rand() % 3) + 2) / 10);
	int scale_multiplier = sprite == L"assets/asteroids/asteroid_large.png" ? 190 : 250; // Sprites have different sizes.
	collider->radius = transform->scale * scale_multiplier;

	// Randomize values.
	asteroid_controller->movement_direction.XValue = transform->position.XValue < 0 ? (float)(rand() % 10) : -(float)(rand() % 10);
	asteroid_controller->movement_direction.YValue = transform->position.YValue < 0 ? (float)(rand() % 10) : -(float)(rand() % 10);
	asteroid_controller->movement_speed = (float)(rand() % 100);
	asteroid_controller->rotation_speed = (float)(rand() % 5 + 1);
	asteroid_controller->rotation_direction = rand() % 2 == 1 ? CLOCKWISE : COUNTERCLOCKWISE;

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::ApplyPrefab_EnemyShip(std::shared_ptr<GameObject> game_object) {
	auto transform = game_object->GetComponent<Component_Transform>();
	auto collider = game_object->GetComponent<Component_EnemyShipCollider>();
	auto sprite_renderer = game_object->GetComponent<Component_SpriteRenderer>();
	auto animator = game_object->GetComponent<Component_Animator>();
	auto enemy_ship_controller = game_object->GetComponent<Component_EnemyShipController>();
	
	transform->scale = 0.2f;
	collider->radius = 50;
	sprite_renderer->SetSprite(L"assets/spaceships/spaceship_purple.png");

	// Randomize spawn position.
	if (rand() % 2 == 1) {
		transform->position.XValue = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
		transform->position.YValue = (float)(rand() % 2000 - 1000);
	}
	else {
		transform->position.XValue = (float)(rand() % 2000 - 1000);
		transform->position.YValue = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
	}

	std::vector<Sprite> sprites = {
		L"assets/spaceships/purple_ship_explosion_1.png",
		L"assets/spaceships/purple_ship_explosion_2.png",
		L"assets/spaceships/purple_ship_explosion_3.png",
		L"assets/spaceships/purple_ship_explosion_4.png",
	};
	std::shared_ptr<Animation> animation = std::make_shared<Animation>("enemy ship explosion", sprites, false, 15);
	animator->RegisterAnimation(animation);

	enemy_ship_controller->movement_speed = 0.8f;

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::ApplyPrefab_Boss(std::shared_ptr<GameObject> game_object) {
	auto transform = game_object->GetComponent<Component_Transform>();
	auto sprite_renderer = game_object->GetComponent<Component_SpriteRenderer>();
	auto boss_controller = game_object->GetComponent<Component_BossController>();
	auto animator = game_object->GetComponent<Component_Animator>();
	auto collider = game_object->GetComponent<Component_BossCollider>();

	std::vector<Sprite> sprites = {
		L"assets/spaceships/purple_ship_explosion_1.png",
		L"assets/spaceships/purple_ship_explosion_2.png",
		L"assets/spaceships/purple_ship_explosion_3.png",
		L"assets/spaceships/purple_ship_explosion_4.png",
	};
	std::shared_ptr<Animation> animation = std::make_shared<Animation>("boss explosion", sprites, false, 15);
	animator->RegisterAnimation(animation);
	
	transform->scale = 0.5f;
	sprite_renderer->SetSprite(L"assets/spaceships/spaceship_boss.png");
	collider->width = 200;
	collider->height = 200;

	boss_controller->movement_speed = 1;
	boss_controller->spawn_position = Vector2D(0, 1500);
	boss_controller->spawn_target = Vector2D(0, 400);
	boss_controller->lasers_shoot_period = 5;
	boss_controller->homing_missile_shoot_period = 5;
	boss_controller->homing_missile_spawn_offset = Vector2D(0, -30);
	#if LOWER_BOSS_HEALTH
		boss_controller->health = BOSS_HEALTH;
	#else
		boss_controller->health = 20;
	#endif

	return game_object;
}
