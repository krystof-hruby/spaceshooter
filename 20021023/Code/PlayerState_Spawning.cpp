// PlayerState_Spawning.cpp
// Krystof Hruby
// 2023

#include "PlayerState_Spawning.h"

#include "Component_PlayerController.h"
#include "GameObject.h"

void PlayerState_Spawning::Play(std::shared_ptr<Component_PlayerController> player_controller) {
	if (player_controller->GetGameObject()->GetComponent<Component_Animator>()->AnimationFinished("player spawn")) {
		player_controller->GetGameObject()->GetComponent<Component_Transform>()->scale = 0.3f;
		player_controller->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = true;

		player_controller->ChangeState(player_controller->state_flying);
	}
}
