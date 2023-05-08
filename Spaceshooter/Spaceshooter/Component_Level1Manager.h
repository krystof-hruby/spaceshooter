// Component_Level1Manager.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_ScriptedEvent_CommanderTalk.h"
#include "Component_Transform.h"

class Component_Level1Manager : public Component, public std::enable_shared_from_this<Component_Level1Manager> {
public:
	using Component::Component;
	inline bool Startable() const override { return false; }
	void Update() override;

	float level_length = 1;
	float spawn_commander_frame_time = 1;
	float start_intro_time = 1;
	float spawn_player_time = 1;
	float start_spawning_asteroids_time = 1;
	float cutscene1_time = 1;
	float cutscene2_time = 1;
	float cutscene3_time = 1;

	std::weak_ptr<Component_ScriptedEvent_CommanderTalk> scripted_event_commander_talk;
	std::weak_ptr<Component_Transform> commander_frame_transform;

private:
	float level_time = 0;
	bool commander_frame_spawned = false;
	bool intro_activated = false;
	bool player_spawned = false;
	bool asteroids_spawned = false;
	bool cutscene1_activated = false;
	bool cutscene2_activated = false;
	bool cutscene3_activated = false;
};

