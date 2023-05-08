// GameObjectFactory.h
// Krystof Hruby
// 2023

#include "GameObjectFactory.h"

#include "AudioClips.h"
#include "Component_Animator.h"
#include "Component_AsteroidCollider.h"
#include "Component_AsteroidController.h"
#include "Component_AsteroidsManager.h"
#include "Component_BossCollider.h"
#include "Component_BossController.h"
#include "Component_CircleCollider.h"
#include "Component_EnemyShipCollider.h"
#include "Component_EnemyShipController.h"
#include "Component_EnemyShipsManager.h"
#include "Component_HomingMissileCollider.h"
#include "Component_HomingMissileController.h"
#include "Component_InputReader.h"
#include "Component_Level1Manager.h"
#include "Component_Level2Manager.h"
#include "Component_Level3Manager.h"
#include "Component_MineCollider.h"
#include "Component_MineController.h"
#include "Component_PlayerBulletCollider.h"
#include "Component_PlayerBulletController.h"
#include "Component_PlayerCollider.h"
#include "Component_PlayerController.h"
#include "Component_PlayerInput.h"
#include "Component_RectangleCollider.h"
#include "Component_ScriptedEvent_CommanderTalk.h"
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

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Level1Manager(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Level 1 Manager";

	auto level1manager = game_object->AddComponent<Component_Level1Manager>();
	level1manager->level_length = 160;
	level1manager->spawn_commander_frame_time = 4;
	level1manager->start_intro_time = 5;
	level1manager->spawn_player_time = 30;
	level1manager->start_spawning_asteroids_time = 65;
	level1manager->cutscene1_time = 90;
	level1manager->cutscene2_time = 115;
	level1manager->cutscene3_time = 140;

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Level2Manager(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Level 2 Manager";

	auto level2manager = game_object->AddComponent<Component_Level2Manager>();

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_Level3Manager(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Level 3 Manager";

	auto level3manager = game_object->AddComponent<Component_Level3Manager>();

	return game_object;
}

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
	animator->LoadAnimation(std::make_shared<Animation>("player explode", ANIMATION_BLUE_SHIP_EXPLOSION, 10, false, 15));
	animator->LoadAnimation(std::make_shared<Animation>("player spawn", ANIMATION_BLUE_SHIP_SPAWN, 10, false, 11));
	animator->LoadAnimation(std::make_shared<Animation>("player despawn", ANIMATION_BLUE_SHIP_DESPAWN, 10, false, 11));

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
	animator->LoadAnimation(std::make_shared<Animation>("asteroid explosion", ANIMATION_ASTEROID_EXPLOSION, 7, false, 15));

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
	animator->LoadAnimation(std::make_shared<Animation>("enemy ship explosion", ANIMATION_PURPLE_SHIP_EXPLOSION, 8, false, 15));

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
	animator->LoadAnimation(std::make_shared<Animation>("boss explosion", ANIMATION_PURPLE_SHIP_EXPLOSION, 7, false, 15));
	animator->LoadAnimation(std::make_shared<Animation>("boss hurt", ANIMATION_BOSS_HURT, 7, false, 10));

	auto collider = game_object->AddComponent<Component_BossCollider>();
	collider->width = 200;
	collider->height = 200;

	auto boss_controller = game_object->AddComponent<Component_BossController>();
	#if DIFFERENT_BOSS_HEALTH
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
	animator->LoadAnimation(std::make_shared<Animation>("homing missile spawn", ANIMATION_PROJECTILE_YELLOW_SPAWN, 8, false, 18));
	animator->LoadAnimation(std::make_shared<Animation>("homing missile explosion", ANIMATION_PROJECTILE_YELLOW_EXPLODE, 8, false, 18));

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
	animator->LoadAnimation(std::make_shared<Animation>("mine spawn", ANIMATION_MINE_SPAWN, 6, false, 15));
	animator->LoadAnimation(std::make_shared<Animation>("mine explosion", ANIMATION_ASTEROID_EXPLOSION, 6, false, 15));

	auto collider = game_object->AddComponent<Component_MineCollider>();
	collider->radius = 50;

	auto mine_controller = game_object->AddComponent<Component_MineController>();
	
	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_UI_Commander(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Commander UI";

	auto transform = game_object->AddComponent<Component_Transform>();
	transform->position = Vector2D(-1300, -600);
	transform->scale = 0; // Grow to 0.4f.

	auto sprite_renderer = game_object->AddComponent<Component_SpriteRenderer>();
	sprite_renderer->SetSprite(SPRITE_COMMANDER_FRAME);
	sprite_renderer->layer = 14;

	auto animator = game_object->AddComponent<Component_Animator>();
	animator->LoadAnimation(std::make_shared<Animation>("commander talk", ANIMATION_COMMANDER_TALK, 15, true, 10));
	animator->LoadAnimation(std::make_shared<Animation>("commander spawn", ANIMATION_COMMANDER_SPAWN, 15, false, 2));
	animator->LoadAnimation(std::make_shared<Animation>("commander despawn", ANIMATION_COMMANDER_DESPAWN, 15, false, 2));

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_UI_Text(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Text UI";

	auto transform = game_object->AddComponent<Component_Transform>();
	transform->position = Vector2D(-150, -600);

	auto animator = game_object->AddComponent<Component_Animator>();
	animator->LoadAnimation(std::make_shared<Animation>("text level 1 intro", TEXT_LEVEL1_INTRO, 15, false, 0.8));
	animator->LoadAnimation(std::make_shared<Animation>("text level 1 cutscene 1", TEXT_LEVEL1_CUTSCENE1, 15, false, 0.2));
	animator->LoadAnimation(std::make_shared<Animation>("text level 1 cutscene 2", TEXT_LEVEL1_CUTSCENE2, 15, false, 0.2));
	animator->LoadAnimation(std::make_shared<Animation>("text level 1 cutscene 3", TEXT_LEVEL1_CUTSCENE3, 15, false, 0.2));
	animator->LoadAnimation(std::make_shared<Animation>("text level 1 outro", TEXT_LEVEL1_OUTRO, 15, false, 0.8));

	return game_object;
}

std::shared_ptr<GameObject> GameObjectFactory::CreateGameObject_ScriptedEvents(std::shared_ptr<ComponentRegistry> component_registry) {
	std::shared_ptr<GameObject> game_object = std::make_shared<GameObject>(component_registry);
	game_object->tag = "Scripted Events";

	game_object->AddComponent<Component_ScriptedEvent_CommanderTalk>();

	return game_object;
}
