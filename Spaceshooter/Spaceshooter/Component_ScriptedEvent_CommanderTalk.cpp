// Component_ScriptedEvent_CommanderTalk.h
// Krystof Hruby
// 2023

#include "Component_ScriptedEvent_CommanderTalk.h"

#include "AudioClips.h"
#include "Time.h"

void Component_ScriptedEvent_CommanderTalk::Start() {
	this->current_phase = this->phase_deactivated;
}

void Component_ScriptedEvent_CommanderTalk::Update() {
	this->current_phase->Play(this->shared_from_this());
}

void Component_ScriptedEvent_CommanderTalk::Activate(std::string text_animation, bool skip_spawning_phase) {
	if (this->activated && !this->finished)
		return;

	this->text_animation = text_animation;
	this->activated = true;
	this->finished = false;

	if (skip_spawning_phase)
		this->current_phase = this->phase_start_talk;
	else
		this->current_phase = this->phase_spawn_commander;
}

void Component_ScriptedEvent_CommanderTalk::Deactivate() {
	this->activated = false;
	this->finished = true;
	this->current_phase = this->phase_deactivated;
	this->commander_ui_animator.lock()->StopAnimation();
	this->text_ui_animator.lock()->StopAnimation();
}

void CommanderTalkPhase_SpawnCommander::Play(std::shared_ptr<Component_ScriptedEvent_CommanderTalk> commander_talk) {
	commander_talk->commander_ui_animator.lock()->PlayAnimation("commander spawn");
	commander_talk->ChangePhase(commander_talk->phase_start_talk);
}

void CommanderTalkPhase_StartTalk::Play(std::shared_ptr<Component_ScriptedEvent_CommanderTalk> commander_talk) {
	// If finished spawning, start talking.
	if (commander_talk->commander_ui_animator.lock()->AnimationFinished("commander spawn")) {
		commander_talk->commander_ui_animator.lock()->PlayAnimation("commander talk");
		commander_talk->text_ui_animator.lock()->PlayAnimation(commander_talk->text_animation);
		commander_talk->commander_talk_sound_index = AudioPlayer::GetInstance().PlayAudioClip(AUDIO_COMMANDER_TALK, 85, true);
		commander_talk->ChangePhase(commander_talk->phase_talking);
	}
}

void CommanderTalkPhase_Talking::Play(std::shared_ptr<Component_ScriptedEvent_CommanderTalk> commander_talk) {
	// If finished talking, start despawning.
	if (commander_talk->text_ui_animator.lock()->AnimationFinished(commander_talk->text_animation)) {
		AudioPlayer::GetInstance().StopAudioClip(commander_talk->commander_talk_sound_index);
		commander_talk->commander_ui_animator.lock()->PlayAnimation("commander despawn");
		commander_talk->ChangePhase(commander_talk->phase_despawning_commander);
	}
}

void CommanderTalkPhase_DespawnCommander::Play(std::shared_ptr<Component_ScriptedEvent_CommanderTalk> commander_talk) {
	// Reset if finished despawnig.
	if (commander_talk->commander_ui_animator.lock()->AnimationFinished("commander despawn")) {
		commander_talk->ChangePhase(commander_talk->phase_deactivated);
		commander_talk->finished = true;
		commander_talk->activated = false;
	}
}
