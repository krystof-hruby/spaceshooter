// Component_Level2Manager.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_ScriptedEvent_CommanderTalk.h"
#include "Component_Transform.h"

class Component_PlayerController;

class Component_Level2Manager : public Component, public std::enable_shared_from_this<Component_Level2Manager> {
public:
	using Component::Component;
	inline bool Startable() const override { return false; }
	void Update() override;

	float level_length = 1;
	float fade_in_time = 1;
	float spawn_commander_frame_time = 1;
	float intro_time = 1;
	float spawn_player_time = 1;
	float start_spawning_asteroids_time = 1;
	float start_spawning_enemy_ships_time = 1;
	float cutscene1_time = 1;
	float cutscene2_time = 1;
	float cutscene3_time = 1;
	float outro_time = 1;
	float despawn_player_time = 1;
	float despawn_commander_frame_time = 1;
	float fade_out_time = 1;
	float level_failed_length = 1;
	float level_failed_despawn_commander_frame_time = 1;
	float level_failed_fade_out_time = 1;

	std::weak_ptr<Component_SpriteRenderer> fader_sprite_renderer;
	std::weak_ptr<Component_ScriptedEvent_CommanderTalk> scripted_event_commander_talk;
	std::weak_ptr<Component_Transform> commander_frame_transform;

	void LevelFailed();

private:
	float level_time = 0;
	float level_failed_time = 0;
	bool faded_in = false;
	bool commander_frame_spawned = false;
	bool intro_activated = false;
	bool player_spawned = false;
	bool asteroids_spawned = false;
	bool enemy_ships_spawned = false;
	bool cutscene1_activated = false;
	bool cutscene2_activated = false;
	bool cutscene3_activated = false;
	bool outro_activated = false;
	bool despawned_player = false;
	bool commander_frame_despawned = false;
	bool faded_out = false;
	bool level_failed = false;
	bool level_failed_commander_frame_despawned = false;

	std::weak_ptr<Component_PlayerController> player_controller;
};

