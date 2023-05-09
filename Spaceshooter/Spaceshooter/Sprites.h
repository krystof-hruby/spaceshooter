// Sprites.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_SpriteRenderer.h" // For Sprite.

// Relative paths to all sprite assets used in the project.

// Sprites:

const Sprite SPRITE_FADER = L"assets/sprites/backgrounds/black.png";

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

const Sprite SPRITE_COMMANDER_FRAME = L"assets/sprites/ui/commander_0.png";

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
const std::vector<Sprite> ANIMATION_BLUE_SHIP_DESPAWN = {
	L"assets/sprites/spaceships/blue_ship_spawn_4.png",
	L"assets/sprites/spaceships/blue_ship_spawn_3.png",
	L"assets/sprites/spaceships/blue_ship_spawn_2.png",
	L"assets/sprites/spaceships/blue_ship_spawn_1.png",
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

const std::vector<Sprite> ANIMATION_COMMANDER_TALK = {
	L"assets/sprites/ui/commander_1.png",
	L"assets/sprites/ui/commander_2.png",
	L"assets/sprites/ui/commander_3.png",
	L"assets/sprites/ui/commander_4.png",
	L"assets/sprites/ui/commander_5.png",
};
const std::vector<Sprite> ANIMATION_COMMANDER_SPAWN = {
	L"assets/sprites/ui/commander_grey_1.png",
	L"assets/sprites/ui/commander_grey_2.png",
};
const std::vector<Sprite> ANIMATION_COMMANDER_DESPAWN = {
	L"assets/sprites/ui/commander_grey_2.png",
	L"assets/sprites/ui/commander_grey_1.png",
};

// Text:
const std::vector<Sprite> TEXT_FAIL = {
	L"assets/sprites/text/dots_1.png",
	L"assets/sprites/text/dots_2.png",
	L"assets/sprites/text/dots_3.png",
	L"assets/sprites/text/dots_3.png",

	L"assets/sprites/text/fail_1.png",
	L"assets/sprites/text/fail_1.png",
	L"assets/sprites/text/fail_1.png",
	L"assets/sprites/text/fail_1.png",
	
	L"assets/sprites/text/fail_2.png",
	L"assets/sprites/text/fail_2.png",
	L"assets/sprites/text/fail_2.png",
	L"assets/sprites/text/fail_2.png",
};

const std::vector<Sprite> TEXT_LEVEL1_INTRO = {
	L"assets/sprites/text/level1_intro_1.png",
	L"assets/sprites/text/level1_intro_1.png",
	L"assets/sprites/text/level1_intro_1.png",
	L"assets/sprites/text/level1_intro_1.png",

	L"assets/sprites/text/level1_intro_2.png",
	L"assets/sprites/text/level1_intro_2.png",
	L"assets/sprites/text/level1_intro_2.png",
	L"assets/sprites/text/level1_intro_2.png",
	
	L"assets/sprites/text/level1_intro_3.png",
	L"assets/sprites/text/level1_intro_3.png",
	L"assets/sprites/text/level1_intro_3.png",
	L"assets/sprites/text/level1_intro_3.png",
	
	L"assets/sprites/text/level1_intro_4.png",
	L"assets/sprites/text/level1_intro_4.png",
	L"assets/sprites/text/level1_intro_4.png",
	L"assets/sprites/text/level1_intro_4.png",
	
	L"assets/sprites/text/level1_intro_5.png",
	L"assets/sprites/text/level1_intro_5.png",
	L"assets/sprites/text/level1_intro_5.png",
	L"assets/sprites/text/level1_intro_5.png",

	L"assets/sprites/text/tutorial_1.png",
	L"assets/sprites/text/tutorial_1.png",
	L"assets/sprites/text/tutorial_1.png",
	L"assets/sprites/text/tutorial_1.png",
	
	L"assets/sprites/text/tutorial_2.png",
	L"assets/sprites/text/tutorial_2.png",
	L"assets/sprites/text/tutorial_2.png",
	L"assets/sprites/text/tutorial_2.png",
	
	L"assets/sprites/text/dots_1.png",
	L"assets/sprites/text/dots_2.png",
	L"assets/sprites/text/dots_3.png",
	L"assets/sprites/text/dots_3.png",
	
	L"assets/sprites/text/tutorial_3.png",
	L"assets/sprites/text/tutorial_3.png",
	L"assets/sprites/text/tutorial_3.png",
	L"assets/sprites/text/tutorial_3.png",
	
	L"assets/sprites/text/tutorial_4.png",
	L"assets/sprites/text/tutorial_4.png",
	L"assets/sprites/text/tutorial_4.png",
	L"assets/sprites/text/tutorial_4.png",
	
	L"assets/sprites/text/dots_1.png",
	L"assets/sprites/text/dots_2.png",
	L"assets/sprites/text/dots_3.png",
	L"assets/sprites/text/dots_3.png",
	
	L"assets/sprites/text/tutorial_5.png",
	L"assets/sprites/text/tutorial_5.png",
	L"assets/sprites/text/tutorial_5.png",
	L"assets/sprites/text/tutorial_5.png",
	
	L"assets/sprites/text/tutorial_6.png",
	L"assets/sprites/text/tutorial_6.png",
	L"assets/sprites/text/tutorial_6.png",
	L"assets/sprites/text/tutorial_6.png",
	
	L"assets/sprites/text/tutorial_7.png",
	L"assets/sprites/text/tutorial_7.png",
	L"assets/sprites/text/tutorial_7.png",
	L"assets/sprites/text/tutorial_7.png",
};

const std::vector<Sprite> TEXT_LEVEL1_CUTSCENE1 = {
	L"assets/sprites/text/level1_cutscene_1.png",
};

const std::vector<Sprite> TEXT_LEVEL1_CUTSCENE2 = {
	L"assets/sprites/text/level1_cutscene_2.png",
};

const std::vector<Sprite> TEXT_LEVEL1_CUTSCENE3 = {
	L"assets/sprites/text/level1_cutscene_3.png",
};

const std::vector<Sprite> TEXT_LEVEL1_OUTRO = {
	L"assets/sprites/text/level1_outro_1.png",
	L"assets/sprites/text/level1_outro_1.png",
	L"assets/sprites/text/level1_outro_1.png",
	L"assets/sprites/text/level1_outro_1.png",

	L"assets/sprites/text/dots_1.png",
	L"assets/sprites/text/dots_2.png",
	L"assets/sprites/text/dots_3.png",
	L"assets/sprites/text/dots_3.png",
	
	L"assets/sprites/text/level1_outro_2.png",
	L"assets/sprites/text/level1_outro_2.png",
	L"assets/sprites/text/level1_outro_2.png",
	L"assets/sprites/text/level1_outro_2.png",
};

const std::vector<Sprite> TEXT_LEVEL2_INTRO = {
	L"assets/sprites/text/dots_1.png",
	L"assets/sprites/text/dots_2.png",
	L"assets/sprites/text/dots_3.png",
	L"assets/sprites/text/dots_3.png",

	L"assets/sprites/text/level2_intro_1.png",
	L"assets/sprites/text/level2_intro_1.png",
	L"assets/sprites/text/level2_intro_1.png",
	L"assets/sprites/text/level2_intro_1.png",
	
	L"assets/sprites/text/level2_intro_2.png",
	L"assets/sprites/text/level2_intro_2.png",
	L"assets/sprites/text/level2_intro_2.png",
	L"assets/sprites/text/level2_intro_2.png",

	L"assets/sprites/text/level2_intro_3.png",
	L"assets/sprites/text/level2_intro_3.png",
	L"assets/sprites/text/level2_intro_3.png",
	L"assets/sprites/text/level2_intro_3.png",

	L"assets/sprites/text/level2_intro_4.png",
	L"assets/sprites/text/level2_intro_4.png",
	L"assets/sprites/text/level2_intro_4.png",
	L"assets/sprites/text/level2_intro_4.png",

	L"assets/sprites/text/level2_intro_5.png",
	L"assets/sprites/text/level2_intro_5.png",
	L"assets/sprites/text/level2_intro_5.png",
	L"assets/sprites/text/level2_intro_5.png",

	L"assets/sprites/text/level2_intro_6.png",
	L"assets/sprites/text/level2_intro_6.png",
	L"assets/sprites/text/level2_intro_6.png",
	L"assets/sprites/text/level2_intro_6.png",
};

const std::vector<Sprite> TEXT_LEVEL2_CUTSCENE1 = {
	L"assets/sprites/text/level2_cutscene_1.png",
};

const std::vector<Sprite> TEXT_LEVEL2_CUTSCENE2 = {
	L"assets/sprites/text/level2_cutscene_2.png",
};

const std::vector<Sprite> TEXT_LEVEL2_CUTSCENE3 = {
	L"assets/sprites/text/level2_cutscene_3.png",
};

const std::vector<Sprite> TEXT_LEVEL2_OUTRO = {
	L"assets/sprites/text/level2_outro_1.png",
	L"assets/sprites/text/level2_outro_1.png",
	L"assets/sprites/text/level2_outro_1.png",
	L"assets/sprites/text/level2_outro_1.png",

	L"assets/sprites/text/level2_outro_2.png",
	L"assets/sprites/text/level2_outro_2.png",
	L"assets/sprites/text/level2_outro_2.png",
	L"assets/sprites/text/level2_outro_2.png",
};

const std::vector<Sprite> TEXT_LEVEL3_INTRO = {
	L"assets/sprites/text/level3_intro_1.png",
	L"assets/sprites/text/level3_intro_1.png",
	L"assets/sprites/text/level3_intro_1.png",
	L"assets/sprites/text/level3_intro_1.png",

	L"assets/sprites/text/level3_intro_2.png",
	L"assets/sprites/text/level3_intro_2.png",
	L"assets/sprites/text/level3_intro_2.png",
	L"assets/sprites/text/level3_intro_2.png",

	L"assets/sprites/text/level3_intro_3.png",
	L"assets/sprites/text/level3_intro_3.png",
	L"assets/sprites/text/level3_intro_3.png",
	L"assets/sprites/text/level3_intro_3.png",

	L"assets/sprites/text/level3_intro_4.png",
	L"assets/sprites/text/level3_intro_4.png",
	L"assets/sprites/text/level3_intro_4.png",
	L"assets/sprites/text/level3_intro_4.png",

};

const std::vector<Sprite> TEXT_LEVEL3_CUTSCENE1 = {
	L"assets/sprites/text/level3_cutscene_1.png",
};

const std::vector<Sprite> TEXT_LEVEL3_CUTSCENE2 = {
	L"assets/sprites/text/level3_cutscene_2.png",
};

const std::vector<Sprite> TEXT_LEVEL3_CUTSCENE3 = {
	L"assets/sprites/text/level3_cutscene_3.png",
};

const std::vector<Sprite> TEXT_LEVEL3_OUTRO = {
	L"assets/sprites/text/level3_outro_1.png",
	L"assets/sprites/text/level3_outro_1.png",
	L"assets/sprites/text/level3_outro_1.png",
	L"assets/sprites/text/level3_outro_1.png",

	L"assets/sprites/text/level3_outro_2.png",
	L"assets/sprites/text/level3_outro_2.png",
	L"assets/sprites/text/level3_outro_2.png",
	L"assets/sprites/text/level3_outro_2.png",

	L"assets/sprites/text/level3_outro_3.png",
	L"assets/sprites/text/level3_outro_3.png",
	L"assets/sprites/text/level3_outro_3.png",
	L"assets/sprites/text/level3_outro_3.png",

	L"assets/sprites/text/level3_outro_4.png",
	L"assets/sprites/text/level3_outro_4.png",
	L"assets/sprites/text/level3_outro_4.png",
	L"assets/sprites/text/level3_outro_4.png",
};