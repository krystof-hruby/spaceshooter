// Component_MineController.cpp
// Krystof Hruby
// 2023

#include "Component_MineController.h"

#include "AudioClips.h"
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
	if (this->GetGameObject()->GetComponent<Component_Animator>()->AnimationFinished("mine explosion"))
		this->GetGameObject()->Destroy();

	if (this->exploded)
		return;

	if (this->GetGameObject()->GetComponent<Component_Animator>()->AnimationFinished("mine spawn"))
		this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = true;
}

bool Component_MineController::IsNearPosition(Vector2D position, float delta) {
	bool is_near_x = (this->spawn_position.XValue < position.XValue + delta) && (this->spawn_position.XValue > position.XValue - delta);
	bool is_near_y = (this->spawn_position.YValue < position.YValue + delta) && (this->spawn_position.YValue > position.YValue - delta);
	return is_near_x && is_near_y;
}

void Component_MineController::Explode() {
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false;
	this->GetGameObject()->GetComponent<Component_MineCollider>()->is_active = false;
	this->GetGameObject()->GetComponent<Component_Transform>()->scale = 0.35f;
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("mine explosion");
	AudioPlayer::GetInstance().PlayAudioClip(AUDIO_MINE_EXPLOSION, 85);
	this->exploded = true;
}
