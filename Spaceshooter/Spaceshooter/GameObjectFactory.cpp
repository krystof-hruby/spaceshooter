// GameObjectFactory.h
// Krystof Hruby
// 2023

#include "GameObjectFactory.h"

#include "AudioClips.h"
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
#include "Component_LaserController.h"
#include "Component_MineCollider.h"
#include "Component_MineController.h"
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
#include "Sprites.h"

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
	sprite_renderer->SetSprite(SPACESHIP_GREEN);

	auto animator = game_object->AddComponent<Component_Animator>();
	animator->RegisterAnimation(std::make_shared<Animation>("player explode", BLUE_SHIP_EXPLOSION, false, 15));
	animator->RegisterAnimation(std::make_shared<Animation>("player spawn", BLUE_SHIP_SPAWN, false, 11));

	auto audio_emitter = game_object->AddComponent<Component_AudioEmitter>();
	audio_emitter->Load(PLAYER_PROJECTILE);
	audio_emitter->SetVolume(PLAYER_PROJECTILE, 70);
	audio_emitter->Load(PLAYER_EXPLOSION);
	audio_emitter->SetVolume(PLAYER_EXPLOSION, 80);
	audio_emitter->Load(PLAYER_SPAWN);
	audio_emitter->SetVolume(PLAYER_SPAWN, 80);

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
	sprite_renderer->SetSprite(PROJECTILE_PINK);

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
	Sprite sprite = rand() % 2 == 1 ? ASTEROID_LARGE : ASTEROID_SMALL;
	sprite_renderer->SetSprite(sprite);

	auto animator = game_object->AddComponent<Component_Animator>();
	game_object->GetComponent<Component_Animator>()->RegisterAnimation(std::make_shared<Animation>("asteroid explosion", ASTEROID_EXPLOSION, false, 15));

	auto audio_emitter = game_object->AddComponent<Component_AudioEmitter>();
	audio_emitter->Load(ASTEROID_WHOOSH);

	auto collider = game_object->AddComponent<Component_AsteroidCollider>();
	int scale_multiplier = sprite == ASTEROID_LARGE ? 190 : 250; // Sprites have different sizes.
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
	sprite_renderer->SetSprite(SPACESHIP_PURPLE);

	auto animator = game_object->AddComponent<Component_Animator>();
	animator->RegisterAnimation(std::make_shared<Animation>("enemy ship explosion", PURPLE_SHIP_EXPLOSION, false, 15));

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
	sprite_renderer->SetSprite(SPACESHIP_BOSS);

	auto animator = game_object->AddComponent<Component_Animator>();
	animator->RegisterAnimation(std::make_shared<Animation>("boss explosion", PURPLE_SHIP_EXPLOSION, false, 15));
	animator->RegisterAnimation(std::make_shared<Animation>("boss hurt", BOSS_HURT, false, 10));

	auto collider = game_object->AddComponent<Component_BossCollider>();
	collider->width = 200;
	collider->height = 200;

	auto boss_controller = game_object->AddComponent<Component_BossController>();
	#if LOWER_BOSS_HEALTH
		boss_controller->health = BOSS_HEALTH;
	#else
		boss_controller->health = 100;
	#endif
	boss_controller->movement_speed = 0.8f;
	boss_controller->floating_movement_speed = 60;
	boss_controller->spawn_position = Vector2D(0, 1500);
	boss_controller->floating_spots.push_back(Vector2D(0, 400));
	boss_controller->floating_spots.push_back(Vector2D(-800, 600));
	boss_controller->floating_spots.push_back(Vector2D(-800, -600));
	boss_controller->floating_spots.push_back(Vector2D(800, -600));
	boss_controller->floating_spots.push_back(Vector2D(800, 600));
	boss_controller->moving_to_floating_spot_period = 13;
	boss_controller->attack_period = 3;
	boss_controller->homing_missile_spawn_offset = Vector2D(0, -200);
	boss_controller->number_of_mines = 9;
	boss_controller->laser_positions[0] = Vector2D(350, 0);
	boss_controller->laser_positions[-PI / 2] = Vector2D(0, 350);
	boss_controller->laser_positions[-PI] = Vector2D(-350, 0);
	boss_controller->laser_positions[PI / 2] = Vector2D(0, -350);

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_HomingMissile(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Homing Missile";

	auto transform = game_object->AddComponent<Component_Transform>();
	transform->scale = 0.18f;

	auto sprite_renderer = game_object->AddComponent<Component_SpriteRenderer>();
	sprite_renderer->SetSprite(PROJECTILE_YELLOW);

	auto animator = game_object->AddComponent<Component_Animator>();
	animator->RegisterAnimation(std::make_shared<Animation>("homing missile spawn", PROJECTILE_YELLOW_SPAWN, false, 18));
	animator->RegisterAnimation(std::make_shared<Animation>("homing missile explosion", PROJECTILE_YELLOW_EXPLODE, false, 18));

	auto collider = game_object->AddComponent<Component_HomingMissileCollider>();
	collider->radius = 45;

	auto homing_missile_controller = game_object->AddComponent<Component_HomingMissileController>();
	homing_missile_controller->movement_speed = 0.9f;

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Mine(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Mine";

	auto transform = game_object->AddComponent<Component_Transform>();
	transform->scale = 0.2f;

	auto sprite_renderer = game_object->AddComponent<Component_SpriteRenderer>();
	sprite_renderer->SetSprite(MINE);

	auto animator = game_object->AddComponent<Component_Animator>();
	animator->RegisterAnimation(std::make_shared<Animation>("mine spawn", MINE_SPAWN, false, 15));
	animator->RegisterAnimation(std::make_shared<Animation>("mine explosion", ASTEROID_EXPLOSION, false, 15));

	auto collider = game_object->AddComponent<Component_MineCollider>();
	collider->radius = 50;

	auto mine_controller = game_object->AddComponent<Component_MineController>();

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Laser(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Laser";

	auto transform = game_object->AddComponent<Component_Transform>();
	transform->scale = 0.18f;

	auto sprite_renderer = game_object->AddComponent<Component_SpriteRenderer>();
	sprite_renderer->SetSprite(PROJECTILE_GREEN_LASER);

	auto collider = game_object->AddComponent<Component_RectangleCollider>();
	collider->width = 50;
	collider->height = 380;

	auto laser_controller = game_object->AddComponent<Component_LaserController>();
	laser_controller->laser_period = 0.5f;

	return game_object;
}

