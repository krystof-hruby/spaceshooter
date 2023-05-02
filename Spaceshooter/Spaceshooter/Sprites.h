// Sprites.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_SpriteRenderer.h"

// Relative paths to all sprite assets used in the project.

// Sprites:

const Sprite SPRITE_BACKGROUND_BLACK = L"assets/sprites/backgrounds/background_black.png";
const Sprite SPRITE_BACKGROUND_BROWN = L"assets/sprites/backgrounds/background_brown.png";
const Sprite SPRITE_BACKGROUND_PURPLE = L"assets/sprites/backgrounds/background_purple.png";

const Sprite SPRITE_SPACESHIP_GREEN = L"assets/sprites/spaceships/spaceship_green.png";
const Sprite SPRITE_SPACESHIP_GREEN_LEFT = L"assets/sprites/spaceships/spaceship_green_left.png";
const Sprite SPRITE_SPACESHIP_GREEN_RIGHT = L"assets/sprites/spaceships/spaceship_green_right.png";

const Sprite SPRITE_PROJECTILE_PINK = L"assets/sprites/projectiles/projectile_pink.png";

const Sprite SPRITE_ASTEROID_SMALL = L"assets/sprites/asteroids/asteroid_small.png";
const Sprite SPRITE_ASTEROID_LARGE = L"assets/sprites/asteroids/asteroid_large.png";

const Sprite SPRITE_SPACESHIP_PURPLE = L"assets/sprites/spaceships/spaceship_purple.png";

const Sprite SPRITE_SPACESHIP_BOSS = L"assets/sprites/spaceships/spaceship_boss.png";

const Sprite SPRITE_PROJECTILE_YELLOW = L"assets/sprites/projectiles/projectile_yellow.png";

const Sprite SPRITE_MINE = L"assets/sprites/projectiles/mine.png";

const Sprite SPRITE_PROJECTILE_GREEN_LASER = L"assets/sprites/projectiles/projectile_green_laser.png";

// Animations:

const std::vector<Sprite> ANIMATION_BLUE_SHIP_EXPLOSION = {
	L"assets/sprites/spaceships/blue_ship_explosion_1.png",
	L"assets/sprites/spaceships/blue_ship_explosion_2.png",
	L"assets/sprites/spaceships/blue_ship_explosion_3.png",
	L"assets/sprites/spaceships/blue_ship_explosion_4.png",
};

const std::vector<Sprite> ANIMATION_BLUE_SHIP_SPAWN = {
	L"assets/sprites/spaceships/blue_ship_spawn_1.png",
	L"assets/sprites/spaceships/blue_ship_spawn_2.png",
	L"assets/sprites/spaceships/blue_ship_spawn_3.png",
	L"assets/sprites/spaceships/blue_ship_spawn_4.png",
};

const std::vector<Sprite> ANIMATION_ASTEROID_EXPLOSION = {
	L"assets/sprites/asteroids/asteroid_explosion_1.png",
	L"assets/sprites/asteroids/asteroid_explosion_2.png",
	L"assets/sprites/asteroids/asteroid_explosion_3.png",
	L"assets/sprites/asteroids/asteroid_explosion_4.png",
};

const std::vector<Sprite> ANIMATION_PURPLE_SHIP_EXPLOSION = {
	L"assets/sprites/spaceships/purple_ship_explosion_1.png",
	L"assets/sprites/spaceships/purple_ship_explosion_2.png",
	L"assets/sprites/spaceships/purple_ship_explosion_3.png",
	L"assets/sprites/spaceships/purple_ship_explosion_4.png",
};

const std::vector<Sprite> ANIMATION_BOSS_HURT = {
	L"assets/sprites/spaceships/spaceship_boss_hurt.png"
};

const std::vector<Sprite> ANIMATION_PROJECTILE_YELLOW_SPAWN = {
	L"assets/sprites/projectiles/projectile_yellow_line.png",
	L"assets/sprites/projectiles/projectile_yellow_arrows.png",
	L"assets/sprites/projectiles/projectile_yellow_lines.png",
	L"assets/sprites/projectiles/projectile_yellow.png",
};

const std::vector<Sprite> ANIMATION_PROJECTILE_YELLOW_EXPLODE = {
	L"assets/sprites/projectiles/projectile_yellow.png",
	L"assets/sprites/projectiles/projectile_yellow_arrows.png",
	L"assets/sprites/projectiles/projectile_yellow_lines.png",
	L"assets/sprites/projectiles/projectile_yellow_line.png",
};

const std::vector<Sprite> ANIMATION_MINE_SPAWN = {
	L"assets/sprites/projectiles/mine_spawn_1.png",
	L"assets/sprites/projectiles/mine_spawn_2.png",
	L"assets/sprites/projectiles/mine_spawn_3.png",
};
