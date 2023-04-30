// Sprites.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_SpriteRenderer.h"

// Relative paths to all sprite assets used in the project.

// Sprites:

const Sprite BACKGROUND_BLACK = L"assets/backgrounds/background_black.png";
const Sprite BACKGROUND_BROWN = L"assets/backgrounds/background_brown.png";
const Sprite BACKGROUND_PURPLE = L"assets/backgrounds/background_purple.png";

const Sprite SPACESHIP_GREEN = L"assets/spaceships/spaceship_green.png";
const Sprite SPACESHIP_GREEN_LEFT = L"assets/spaceships/spaceship_green_left.png";
const Sprite SPACESHIP_GREEN_RIGHT = L"assets/spaceships/spaceship_green_right.png";

const Sprite PROJECTILE_PINK = L"assets/projectiles/projectile_pink.png";

const Sprite ASTEROID_SMALL = L"assets/asteroids/asteroid_small.png";
const Sprite ASTEROID_LARGE = L"assets/asteroids/asteroid_large.png";

const Sprite SPACESHIP_PURPLE = L"assets/spaceships/spaceship_purple.png";

const Sprite SPACESHIP_BOSS = L"assets/spaceships/spaceship_boss.png";

const Sprite PROJECTILE_YELLOW = L"assets/projectiles/projectile_yellow.png";

// Animations:

const std::vector<Sprite> BLUE_SHIP_EXPLOSION = {
	L"assets/spaceships/blue_ship_explosion_1.png",
	L"assets/spaceships/blue_ship_explosion_2.png",
	L"assets/spaceships/blue_ship_explosion_3.png",
	L"assets/spaceships/blue_ship_explosion_4.png",
};

const std::vector<Sprite> BLUE_SHIP_SPAWN = {
	L"assets/spaceships/blue_ship_spawn_1.png",
	L"assets/spaceships/blue_ship_spawn_2.png",
	L"assets/spaceships/blue_ship_spawn_3.png",
	L"assets/spaceships/blue_ship_spawn_4.png",
};

const std::vector<Sprite> ASTEROID_EXPLOSION = {
	L"assets/asteroids/asteroid_explosion_1.png",
	L"assets/asteroids/asteroid_explosion_2.png",
	L"assets/asteroids/asteroid_explosion_3.png",
	L"assets/asteroids/asteroid_explosion_4.png",
};

const std::vector<Sprite> PURPLE_SHIP_EXPLOSION = {
	L"assets/spaceships/purple_ship_explosion_1.png",
	L"assets/spaceships/purple_ship_explosion_2.png",
	L"assets/spaceships/purple_ship_explosion_3.png",
	L"assets/spaceships/purple_ship_explosion_4.png",
};

const std::vector<Sprite> PROJECTILE_YELLOW_SPAWN = {
		L"assets/projectiles/projectile_yellow_line.png",
		L"assets/projectiles/projectile_yellow_arrows.png",
		L"assets/projectiles/projectile_yellow.png",
};

const std::vector<Sprite> PROJECTILE_YELLOW_EXPLODE = {
		L"assets/projectiles/projectile_yellow.png",
		L"assets/projectiles/projectile_yellow_arrows.png",
		L"assets/projectiles/projectile_yellow_line.png",
};