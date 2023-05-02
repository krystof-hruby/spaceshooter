#include "PlayerState_Exploding.h"

#include "Component_Animator.h"
#include "Component_PlayerController.h"
#include "GameObject.h"

void PlayerState_Exploding::Play(std::shared_ptr<Component_PlayerController> player_controller) {
	if (player_controller->GetGameObject()->GetComponent<Component_Animator>()->AnimationFinished("player explode")) {
		// Was eliminated.
		player_controller->GetGameObject()->Destroy();

		// TODO: display end screen


		return;
	}
}
