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
#include "Component_HomingMissileCollider.h"
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

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject(GameObjectType type, std::shared_ptr<ComponentRegistry> component_registry) {
	return object_creation_jump_table[type](component_registry);
}

// Specific CreateGameObject methods:

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Background(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Background";

	auto transform = game_object->AddComponent<Component_Transform>();
	transform->rotation = PI / 2;
	
	auto sprite_renderer = game_object->AddComponent<Component_SpriteRenderer>();
	#if VISUALIZE_HITBOXES
		sprite_renderer->is_active = false;
	#endif

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_ScoreManager(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Score Manager";
	
	auto score_manager = game_object->AddComponent<Component_ScoreManager>();
	
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Player(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Player";
	
	auto transform = game_object->AddComponent<Component_Transform>();
	transform->scale = 0.2f;

	auto collider = game_object->AddComponent<Component_PlayerCollider>();
	collider->radius = 45;

	auto sprite_renderer = game_object->AddComponent<Component_SpriteRenderer>();
	sprite_renderer->SetSprite(L"assets/spaceships/spaceship_green.png");

	auto animator = game_object->AddComponent<Component_Animator>();
	std::vector<Sprite> sprites = {
		L"assets/spaceships/blue_ship_explosion_1.png",
		L"assets/spaceships/blue_ship_explosion_2.png",
		L"assets/spaceships/blue_ship_explosion_3.png",
		L"assets/spaceships/blue_ship_explosion_4.png",
	};
	animator->RegisterAnimation(std::make_shared<Animation>("player explode", sprites, false, 15));
	sprites = {
		L"assets/spaceships/blue_ship_spawn_1.png",
		L"assets/spaceships/blue_ship_spawn_2.png",
		L"assets/spaceships/blue_ship_spawn_3.png",
		L"assets/spaceships/blue_ship_spawn_4.png",
	};
	animator->RegisterAnimation(std::make_shared<Animation>("player spawn", sprites, false, 11));

	auto audio_emitter = game_object->AddComponent<Component_AudioEmitter>();

	auto player_input = game_object->AddComponent<Component_PlayerInput>();

	auto player_controller = game_object->AddComponent<Component_PlayerController>();
	player_controller->movement_speed = 500;
	player_controller->rotation_speed = 5;
	player_controller->reload_period = 0.25f;

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_PlayerBullet(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Player Bullet";

	auto transform = game_object->AddComponent<Component_Transform>();
	transform->scale = 0.2f;

	auto sprite_renderer = game_object->AddComponent<Component_SpriteRenderer>();
	sprite_renderer->SetSprite(L"assets/projectiles/projectile_pink.png");

	auto collider = game_object->AddComponent<Component_PlayerBulletCollider>();
	collider->width = 80;
	collider->height = 40;

	auto player_bullet_controller = game_object->AddComponent<Component_PlayerBulletController>();
	player_bullet_controller->movement_speed = 1500;

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Asteroid(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Asteroid";
	
	auto transform = game_object->AddComponent<Component_Transform>();
	// Randomize spawn position.
	if (rand() % 2 == 1) {
		transform->position.XValue = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
		transform->position.YValue = (float)(rand() % 2000 - 1000);
	}
	else {
		transform->position.XValue = (float)(rand() % 2000 - 1000);
		transform->position.YValue = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
	}
	// Randomize scale.
	transform->scale = ((float)((rand() % 3) + 2) / 10);

	auto sprite_renderer = game_object->AddComponent<Component_SpriteRenderer>();
	// Randomize sprite.
	Sprite sprite = rand() % 2 == 1 ? L"assets/asteroids/asteroid_large.png" : L"assets/asteroids/asteroid_small.png";
	sprite_renderer->SetSprite(sprite);

	auto animator = game_object->AddComponent<Component_Animator>();
	std::vector<Sprite> sprites = {
		L"assets/asteroids/asteroid_explosion_1.png",
		L"assets/asteroids/asteroid_explosion_2.png",
		L"assets/asteroids/asteroid_explosion_3.png",
		L"assets/asteroids/asteroid_explosion_4.png",
	};
	game_object->GetComponent<Component_Animator>()->RegisterAnimation(std::make_shared<Animation>("asteroid explosion", sprites, false, 15));

	auto collider = game_object->AddComponent<Component_AsteroidCollider>();
	int scale_multiplier = sprite == L"assets/asteroids/asteroid_large.png" ? 190 : 250; // Sprites have different sizes.
	collider->radius = transform->scale * scale_multiplier;

	auto asteroid_controller = game_object->AddComponent<Component_AsteroidController>();
	// Randomize values.
	asteroid_controller->movement_direction.XValue = transform->position.XValue < 0 ? (float)(rand() % 10) : -(float)(rand() % 10);
	asteroid_controller->movement_direction.YValue = transform->position.YValue < 0 ? (float)(rand() % 10) : -(float)(rand() % 10);
	asteroid_controller->movement_speed = (float)(rand() % 100);
	asteroid_controller->rotation_speed = (float)(rand() % 5 + 1);
	asteroid_controller->rotation_direction = rand() % 2 == 1 ? CLOCKWISE : COUNTERCLOCKWISE;

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_AsteroidsManager(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Asteroids Manager";
	
	auto asteroids_manager = game_object->AddComponent<Component_AsteroidsManager>();

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_EnemyShip(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Enemy Ship";
	
	auto transform = game_object->AddComponent<Component_Transform>();
	transform->scale = 0.2f;
	// Randomize spawn position.
	if (rand() % 2 == 1) {
		transform->position.XValue = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
		transform->position.YValue = (float)(rand() % 2000 - 1000);
	}
	else {
		transform->position.XValue = (float)(rand() % 2000 - 1000);
		transform->position.YValue = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
	}

	auto sprite_renderer = game_object->AddComponent<Component_SpriteRenderer>();
	sprite_renderer->SetSprite(L"assets/spaceships/spaceship_purple.png");

	auto animator = game_object->AddComponent<Component_Animator>();
	std::vector<Sprite> sprites = {
		L"assets/spaceships/purple_ship_explosion_1.png",
		L"assets/spaceships/purple_ship_explosion_2.png",
		L"assets/spaceships/purple_ship_explosion_3.png",
		L"assets/spaceships/purple_ship_explosion_4.png",
	};
	animator->RegisterAnimation(std::make_shared<Animation>("enemy ship explosion", sprites, false, 15));

	auto collider = game_object->AddComponent<Component_EnemyShipCollider>();
	collider->radius = 50;

	auto enemy_ship_controller = game_object->AddComponent<Component_EnemyShipController>();
	enemy_ship_controller->movement_speed = 0.8f;

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_EnemyShipsManager(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Enemy Ships Manager";

	auto enemy_ships_manager = game_object->AddComponent<Component_EnemyShipsManager>();
	
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Boss(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Boss";

	auto transform = game_object->AddComponent<Component_Transform>();
	transform->scale = 0.5f;

	auto sprite_renderer = game_object->AddComponent<Component_SpriteRenderer>();
	sprite_renderer->SetSprite(L"assets/spaceships/spaceship_boss.png");

	auto animator = game_object->AddComponent<Component_Animator>();
	std::vector<Sprite> sprites = {
		L"assets/spaceships/purple_ship_explosion_1.png",
		L"assets/spaceships/purple_ship_explosion_2.png",
		L"assets/spaceships/purple_ship_explosion_3.png",
		L"assets/spaceships/purple_ship_explosion_4.png",
	};
	animator->RegisterAnimation(std::make_shared<Animation>("boss explosion", sprites, false, 15));

	auto collider = game_object->AddComponent<Component_BossCollider>();
	collider->width = 200;
	collider->height = 200;

	auto boss_controller = game_object->AddComponent<Component_BossController>();
	boss_controller->movement_speed = 0.8f;
	boss_controller->floating_movement_speed = 60;
	boss_controller->spawn_position = Vector2D(0, 1500);
	boss_controller->floating_spots.push_back(Vector2D(0, 400));
	boss_controller->floating_spots.push_back(Vector2D(-800, 600));
	boss_controller->floating_spots.push_back(Vector2D(-800, -600));
	boss_controller->floating_spots.push_back(Vector2D(800, -600));
	boss_controller->floating_spots.push_back(Vector2D(800, 600));
	boss_controller->moving_to_floating_spot_period = 10;
	boss_controller->lasers_shoot_period = 5;
	boss_controller->homing_missile_shoot_period = 5;
	boss_controller->homing_missile_spawn_offset = Vector2D(0, -30);
	#if LOWER_BOSS_HEALTH
		boss_controller->health = BOSS_HEALTH;
	#else
		boss_controller->health = 100;
	#endif

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_HomingMissile(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Homing Missile";

	auto transform = game_object->AddComponent<Component_Transform>();

	auto sprite_renderer = game_object->AddComponent<Component_SpriteRenderer>();

	auto animator = game_object->AddComponent<Component_Animator>();
	std::vector<Sprite> sprites = {
		L"assets/spaceships/purple_ship_explosion_1.png", //TODO: change sprites
		L"assets/spaceships/purple_ship_explosion_2.png",
		L"assets/spaceships/purple_ship_explosion_3.png",
		L"assets/spaceships/purple_ship_explosion_4.png",
	};
	animator->RegisterAnimation(std::make_shared<Animation>("homing missile explosion", sprites, false, 15));

	auto collider = game_object->AddComponent<Component_HomingMissileCollider>();
	collider->radius = 50;

	auto homing_missile_controller = game_object->AddComponent<Component_HomingMissileController>();

	return game_object;
}

