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
	sprite_renderer->layer = 0;
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
	sprite_renderer->SetSprite(SPRITE_SPACESHIP_GREEN);
	sprite_renderer->layer = 10;

	auto animator = game_object->AddComponent<Component_Animator>();
	animator->RegisterAnimation(std::make_shared<Animation>("player explode", ANIMATION_BLUE_SHIP_EXPLOSION, 10, false, 15));
	animator->RegisterAnimation(std::make_shared<Animation>("player spawn", ANIMATION_BLUE_SHIP_SPAWN, 10, false, 11));
	animator->RegisterAnimation(std::make_shared<Animation>("player despawn", ANIMATION_BLUE_SHIP_DESPAWN, 10, false, 11));

	auto audio_emitter = game_object->AddComponent<Component_AudioEmitter>();
	audio_emitter->Load(AUDIO_PLAYER_PROJECTILE);
	audio_emitter->SetVolume(AUDIO_PLAYER_PROJECTILE, 68);
	audio_emitter->Load(AUDIO_PLAYER_EXPLOSION);
	audio_emitter->SetVolume(AUDIO_PLAYER_EXPLOSION, 80);
	audio_emitter->Load(AUDIO_PLAYER_SPAWN);
	audio_emitter->SetVolume(AUDIO_PLAYER_SPAWN, 80);

	auto player_input = game_object->AddComponent<Component_PlayerInput>();

	auto player_controller = game_object->AddComponent<Component_PlayerController>();
	player_controller->movement_speed = 500;
	player_controller->rotation_speed = 5;
	player_controller->grace_period = 3;
	player_controller->reload_period = 0.25f;
	player_controller->free_roaming_period = 4;

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_PlayerBullet(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Player Bullet";

	auto transform = game_object->AddComponent<Component_Transform>();
	transform->scale = 0.2f;

	auto sprite_renderer = game_object->AddComponent<Component_SpriteRenderer>();
	sprite_renderer->SetSprite(SPRITE_PROJECTILE_PINK);
	sprite_renderer->layer = 9;

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
	sprite_renderer->layer = 7;
	// Randomize sprite.
	Sprite sprite = rand() % 2 == 1 ? SPRITE_ASTEROID_LARGE : SPRITE_ASTEROID_SMALL;
	sprite_renderer->SetSprite(sprite);

	auto animator = game_object->AddComponent<Component_Animator>();
	animator->RegisterAnimation(std::make_shared<Animation>("asteroid explosion", ANIMATION_ASTEROID_EXPLOSION, 7, false, 15));

	auto audio_emitter = game_object->AddComponent<Component_AudioEmitter>();
	audio_emitter->Load(AUDIO_ASTEROID_EXPLOSION);
	audio_emitter->SetVolume(AUDIO_ASTEROID_EXPLOSION, 75);

	auto collider = game_object->AddComponent<Component_AsteroidCollider>();
	int scale_multiplier = sprite == SPRITE_ASTEROID_LARGE ? 190 : 250; // Sprites have different sizes.
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
	} else {
		transform->position.XValue = (float)(rand() % 2000 - 1000);
		transform->position.YValue = (float)(rand() % 500 + 2000) * (rand() % 2 == 1 ? 1 : -1);
	}

	auto sprite_renderer = game_object->AddComponent<Component_SpriteRenderer>();
	sprite_renderer->SetSprite(SPRITE_SPACESHIP_PURPLE);
	sprite_renderer->layer = 8;

	auto animator = game_object->AddComponent<Component_Animator>();
	animator->RegisterAnimation(std::make_shared<Animation>("enemy ship explosion", ANIMATION_PURPLE_SHIP_EXPLOSION, 8, false, 15));

	auto audio_emitter = game_object->AddComponent<Component_AudioEmitter>();
	audio_emitter->Load(AUDIO_ENEMY_SHIP_EXPLOSION);
	audio_emitter->SetVolume(AUDIO_ENEMY_SHIP_EXPLOSION, 70);

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
	sprite_renderer->SetSprite(SPRITE_SPACESHIP_BOSS);
	sprite_renderer->layer = 7;

	auto animator = game_object->AddComponent<Component_Animator>();
	animator->RegisterAnimation(std::make_shared<Animation>("boss explosion", ANIMATION_PURPLE_SHIP_EXPLOSION, 7, false, 15));
	animator->RegisterAnimation(std::make_shared<Animation>("boss hurt", ANIMATION_BOSS_HURT, 7, false, 10));

	auto audio_emitter = game_object->AddComponent<Component_AudioEmitter>();
	//audio_emitter->Load();

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

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_HomingMissile(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Homing Missile";

	auto transform = game_object->AddComponent<Component_Transform>();
	transform->scale = 0.18f;

	auto sprite_renderer = game_object->AddComponent<Component_SpriteRenderer>();
	sprite_renderer->SetSprite(SPRITE_PROJECTILE_YELLOW);
	sprite_renderer->layer = 8;

	auto animator = game_object->AddComponent<Component_Animator>();
	animator->RegisterAnimation(std::make_shared<Animation>("homing missile spawn", ANIMATION_PROJECTILE_YELLOW_SPAWN, 8, false, 18));
	animator->RegisterAnimation(std::make_shared<Animation>("homing missile explosion", ANIMATION_PROJECTILE_YELLOW_EXPLODE, 8, false, 18));

	auto audio_emitter = game_object->AddComponent<Component_AudioEmitter>();
	audio_emitter->Load(AUDIO_HOMING_MISSILE_EXPLOSION);
	audio_emitter->SetVolume(AUDIO_HOMING_MISSILE_EXPLOSION, 70);

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
	sprite_renderer->SetSprite(SPRITE_MINE);
	sprite_renderer->layer = 6;

	auto animator = game_object->AddComponent<Component_Animator>();
	animator->RegisterAnimation(std::make_shared<Animation>("mine spawn", ANIMATION_MINE_SPAWN, 6, false, 15));
	animator->RegisterAnimation(std::make_shared<Animation>("mine explosion", ANIMATION_ASTEROID_EXPLOSION, 6, false, 15));

	auto audio_emitter = game_object->AddComponent<Component_AudioEmitter>();
	audio_emitter->Load(AUDIO_MINE_EXPLOSION);
	audio_emitter->SetVolume(AUDIO_MINE_EXPLOSION, 70);

	auto collider = game_object->AddComponent<Component_MineCollider>();
	collider->radius = 50;

	auto mine_controller = game_object->AddComponent<Component_MineController>();
	
	return game_object;
}
