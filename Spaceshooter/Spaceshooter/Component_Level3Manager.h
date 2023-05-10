// Component_Level3Manager.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_BossController.h"
#include "Component_ScriptedEvent_CommanderTalk.h"

class Component_PlayerController;

class Component_Level3Manager : public Component, public std::enable_shared_from_this<Component_Level3Manager> {
public:
	using Component::Component;
	inline bool Startable() const override { return false; }
	void Update() override;

	float fade_in_time = 1;
	float spawn_commander_frame_time = 1;
	float intro_time = 1;
	float spawn_player_time = 1;
	float spawn_boss_time = 1;
	float level_failed_length = 1;
	float level_failed_despawn_commander_frame_time = 1;
	float level_failed_fade_out_time = 1;
	float level_finished_length = 1;
	float level_finished_despawn_player_time = 1;
	float level_finished_despawn_commander_frame_time = 1;
	float level_finished_fade_out_time = 1;

	std::weak_ptr<Component_SpriteRenderer> fader_sprite_renderer;
	std::weak_ptr<Component_ScriptedEvent_CommanderTalk> scripted_event_commander_talk;
	std::weak_ptr<Component_Transform> commander_frame_transform;

	void LevelFailed();
	void LevelFinished();

private:
	float level_time = 0;
	float level_failed_time = 0;
	float level_finished_time = 0;
	bool faded_in = false;
	bool commander_frame_spawned = false;
	bool intro_activated = false;
	bool player_spawned = false;
	bool boss_spawned = false;
	bool cutscene1_activated = false;
	bool cutscene2_activated = false;
	bool cutscene3_activated = false;
	bool outro_activated = false;
	bool despawned_player = false;
	bool commander_frame_despawned = false;
	bool faded_out = false;
	bool level_failed = false;
	bool level_failed_commander_frame_despawned = false;
	bool level_finished = false;

	std::weak_ptr<Component_PlayerController> player_controller;
	std::weak_ptr<Component_BossController> boss_controller;
};

