// Sprites.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_SpriteRenderer.h"

// Relative paths to all sprite assets used in the project.

// Sprites:

const Sprite BACKGROUND_BLACK = L"assets/sprites/backgrounds/background_black.png";
const Sprite BACKGROUND_BROWN = L"assets/sprites/backgrounds/background_brown.png";
const Sprite BACKGROUND_PURPLE = L"assets/sprites/backgrounds/background_purple.png";

const Sprite SPACESHIP_GREEN = L"assets/sprites/spaceships/spaceship_green.png";
const Sprite SPACESHIP_GREEN_LEFT = L"assets/sprites/spaceships/spaceship_green_left.png";
const Sprite SPACESHIP_GREEN_RIGHT = L"assets/sprites/spaceships/spaceship_green_right.png";

const Sprite PROJECTILE_PINK = L"assets/sprites/projectiles/projectile_pink.png";

const Sprite ASTEROID_SMALL = L"assets/sprites/asteroids/asteroid_small.png";
const Sprite ASTEROID_LARGE = L"assets/sprites/asteroids/asteroid_large.png";

const Sprite SPACESHIP_PURPLE = L"assets/sprites/spaceships/spaceship_purple.png";

const Sprite SPACESHIP_BOSS = L"assets/sprites/spaceships/spaceship_boss.png";

const Sprite PROJECTILE_YELLOW = L"assets/sprites/projectiles/projectile_yellow.png";

const Sprite MINE = L"assets/sprites/projectiles/mine.png";

const Sprite PROJECTILE_GREEN_LASER = L"assets/sprites/projectiles/projectile_green_laser.png";

// Animations:

const std::vector<Sprite> BLUE_SHIP_EXPLOSION = {
	L"assets/sprites/spaceships/blue_ship_explosion_1.png",
	L"assets/sprites/spaceships/blue_ship_explosion_2.png",
	L"assets/sprites/spaceships/blue_ship_explosion_3.png",
	L"assets/sprites/spaceships/blue_ship_explosion_4.png",
};

const std::vector<Sprite> BLUE_SHIP_SPAWN = {
	L"assets/sprites/spaceships/blue_ship_spawn_1.png",
	L"assets/sprites/spaceships/blue_ship_spawn_2.png",
	L"assets/sprites/spaceships/blue_ship_spawn_3.png",
	L"assets/sprites/spaceships/blue_ship_spawn_4.png",
};

const std::vector<Sprite> ASTEROID_EXPLOSION = {
	L"assets/sprites/asteroids/asteroid_explosion_1.png",
	L"assets/sprites/asteroids/asteroid_explosion_2.png",
	L"assets/sprites/asteroids/asteroid_explosion_3.png",
	L"assets/sprites/asteroids/asteroid_explosion_4.png",
};

const std::vector<Sprite> PURPLE_SHIP_EXPLOSION = {
	L"assets/sprites/spaceships/purple_ship_explosion_1.png",
	L"assets/sprites/spaceships/purple_ship_explosion_2.png",
	L"assets/sprites/spaceships/purple_ship_explosion_3.png",
	L"assets/sprites/spaceships/purple_ship_explosion_4.png",
};

const std::vector<Sprite> BOSS_HURT = {
	L"assets/sprites/spaceships/spaceship_boss_hurt.png"
};

const std::vector<Sprite> PROJECTILE_YELLOW_SPAWN = {
	L"assets/sprites/projectiles/projectile_yellow_line.png",
	L"assets/sprites/projectiles/projectile_yellow_arrows.png",
	L"assets/sprites/projectiles/projectile_yellow_lines.png",
	L"assets/sprites/projectiles/projectile_yellow.png",
};

const std::vector<Sprite> PROJECTILE_YELLOW_EXPLODE = {
	L"assets/sprites/projectiles/projectile_yellow.png",
	L"assets/sprites/projectiles/projectile_yellow_arrows.png",
	L"assets/sprites/projectiles/projectile_yellow_lines.png",
	L"assets/sprites/projectiles/projectile_yellow_line.png",
};

const std::vector<Sprite> MINE_SPAWN = {
	L"assets/sprites/projectiles/mine_spawn_1.png",
	L"assets/sprites/projectiles/mine_spawn_2.png",
	L"assets/sprites/projectiles/mine_spawn_3.png",
};
