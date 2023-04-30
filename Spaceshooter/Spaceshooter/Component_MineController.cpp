// Component_MineController.cpp
// Krystof Hruby
// 2023

#include "Component_MineController.h"

#include "Component_Animator.h"
#include "Component_MineCollider.h"
#include "Component_SpriteRenderer.h"
#include "Component_Transform.h"
#include "GameObject.h"

void Component_MineController::Start() {
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false;
	this->GetGameObject()->GetComponent<Component_Transform>()->position = this->spawn_position;
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("mine spawn");
}

void Component_MineController::Update() {
	if (this->GetGameObject()->GetComponent<Component_Animator>()->AnimationFinished("mine explosion")) {
		this->GetGameObject()->Destroy();
		return;
	}

	if (this->GetGameObject()->GetComponent<Component_Animator>()->AnimationFinished("mine spawn"))
		this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = true;
}

void Component_MineController::Explode() {
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false;
	this->GetGameObject()->GetComponent<Component_MineCollider>()->is_active = false;
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("mine explosion");
}
