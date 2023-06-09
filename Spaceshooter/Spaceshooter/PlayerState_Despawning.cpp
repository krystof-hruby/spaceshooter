// PlayerState_Despawning.cpp
// Krystof Hruby
// 2023

#include "PlayerState_Despawning.h"

#include "Component_PlayerController.h"
#include "GameObject.h"

void PlayerState_Despawning::Play(std::shared_ptr<Component_PlayerController> player_controller) {
	if (player_controller->GetGameObject()->GetComponent<Component_Animator>()->AnimationFinished("player despawn"))
		return;
}
