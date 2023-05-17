// BossState_Exploding.cpp
// Krystof Hruby
// 2023

#include "BossState_Exploding.h"

#include "Component_Animator.h"
#include "Component_BossController.h"
#include "GameObject.h"

void BossState_Exploding::Play(std::shared_ptr<Component_BossController> boss_controller) {
	auto animator = boss_controller->GetGameObject()->GetComponent<Component_Animator>();

	if (animator->AnimationFinished("boss explosion"))
		boss_controller->GetGameObject()->Destroy();
}
