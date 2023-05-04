// PlayerState_GracePeriod.h
// Krystof Hruby
// 2023

#include "PlayerState_GracePeriod.h"

#include "AudioClips.h"
#include "Component_Animator.h"
#include "Component_PlayerController.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "Time.h"

void PlayerState_GracePeriod::Play(std::shared_ptr<Component_PlayerController> player_controller) {
	if (this->grace_period_time > player_controller->grace_period) {
		player_controller->GetGameObject()->GetComponent<Component_Transform>()->scale = 0.31f;
		player_controller->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("player spawn");
		AudioPlayer::GetInstance().PlayAudioClip(AUDIO_PLAYER_SPAWN, 80);
		
		player_controller->ChangeState(player_controller->state_spawning);
	}

	this->grace_period_time += (float)Time::delta_time;
}
