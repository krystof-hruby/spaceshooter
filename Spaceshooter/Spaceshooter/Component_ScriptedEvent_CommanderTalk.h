// Component_ScriptedEvent_CommanderTalk.h
// Krystof Hruby
// 2023

#pragma once

#include <string>
#include "Component_Animator.h"
#include "AudioPlayer.h"

class Component_ScriptedEvent_CommanderTalk;

class CommanderTalkPhase {
public:
	virtual void Play(std::shared_ptr<Component_ScriptedEvent_CommanderTalk> commander_talk) { }

protected:
	CommanderTalkPhase() { }
};

class CommanderTalkPhase_Deactivated : public CommanderTalkPhase {
public:
	void Play(std::shared_ptr<Component_ScriptedEvent_CommanderTalk> commander_talk) override { }
};

class CommanderTalkPhase_SpawnCommander : public CommanderTalkPhase {
public:
	void Play(std::shared_ptr<Component_ScriptedEvent_CommanderTalk> commander_talk) override;
};

class CommanderTalkPhase_StartTalk : public CommanderTalkPhase {
public:
	void Play(std::shared_ptr<Component_ScriptedEvent_CommanderTalk> commander_talk) override;
};

class CommanderTalkPhase_Talking : public CommanderTalkPhase {
public:
	void Play(std::shared_ptr<Component_ScriptedEvent_CommanderTalk> commander_talk) override;
};

class CommanderTalkPhase_DespawnCommander : public CommanderTalkPhase {
public:
	void Play(std::shared_ptr<Component_ScriptedEvent_CommanderTalk> commander_talk) override;
};

class Component_ScriptedEvent_CommanderTalk final : public Component, public std::enable_shared_from_this< Component_ScriptedEvent_CommanderTalk> {
public:
	using Component::Component;
	void Start() override;
	void Update() override;

	std::weak_ptr<Component_Animator> commander_ui_animator;
	std::weak_ptr<Component_Animator> text_ui_animator;

	void Activate(std::string text_animation);
	void Deactivate();
	bool HasFinished() { return this->finished; }

private:
	// For states.
	friend class CommanderTalkPhase_Deactivated;
	friend class CommanderTalkPhase_SpawnCommander;
	friend class CommanderTalkPhase_StartTalk;
	friend class CommanderTalkPhase_Talking;
	friend class CommanderTalkPhase_DespawnCommander;

	std::shared_ptr<CommanderTalkPhase> current_phase;
	void ChangePhase(std::shared_ptr<CommanderTalkPhase> phase) { this->current_phase = phase; }

	// States:
	std::shared_ptr<CommanderTalkPhase_Deactivated> phase_deactivated = std::make_shared<CommanderTalkPhase_Deactivated>();
	std::shared_ptr<CommanderTalkPhase_SpawnCommander> phase_spawn_commander = std::make_shared<CommanderTalkPhase_SpawnCommander>();
	std::shared_ptr<CommanderTalkPhase_StartTalk> phase_start_talk = std::make_shared<CommanderTalkPhase_StartTalk>();
	std::shared_ptr<CommanderTalkPhase_Talking> phase_talking = std::make_shared<CommanderTalkPhase_Talking>();
	std::shared_ptr<CommanderTalkPhase_DespawnCommander> phase_despawning_commander = std::make_shared<CommanderTalkPhase_DespawnCommander>();

	std::string text_animation;
	bool activated = false;
	bool finished = false;
	SoundIndex commander_talk_sound_index;
};

