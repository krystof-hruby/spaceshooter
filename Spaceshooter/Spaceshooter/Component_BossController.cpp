// Component_BossController.cpp
// Krystof Hruby
// 2023

#include "Component_BossController.h"

#include "AudioClips.h"
#include "Component_Animator.h"
#include "Component_BossCollider.h"
#include "Component_HomingMissileController.h"
#include "Component_MineController.h"
#include "GameObjectFactory.h"
#include "Scene.h"

void Component_BossController::Start() {
	this->GetGameObject()->GetComponent<Component_Transform>()->position = this->spawn_position;
	this->ChangeState(this->state_movig_to_floating_spot);
}

void Component_BossController::Update() {
	this->current_state->Play(this->shared_from_this());

	if (this->GetGameObject()->GetComponent<Component_Animator>()->AnimationFinished("boss hurt"))
		this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = true;
}

void Component_BossController::ShootHomingMissile() {
	std::shared_ptr<GameObject> homing_missile = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::HomingMissile, this->GetGameObject()->GetComponentRegistry());
	homing_missile->GetComponent<Component_HomingMissileController>()->player_transform = this->player_transform;
	homing_missile->GetComponent<Component_Transform>()->position = this->GetGameObject()->GetComponent<Component_Transform>()->position + this->homing_missile_spawn_offset;

	Scene::Instantiate(homing_missile);
	this->homing_missiles.push_back(homing_missile);

	AudioPlayer::GetInstance().PlayAudioClip(AUDIO_HOMING_MISSILE_SHOOT, 70);
}

void Component_BossController::SpawnMines() {
	for (int i = 0; i < this->number_of_mines; i++) {
		std::shared_ptr<GameObject> mine = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Mine, this->GetGameObject()->GetComponentRegistry());

		// Randomize spawn position.
		auto mine_controller = mine->GetComponent<Component_MineController>();
		while (true) {
			mine_controller->spawn_position.XValue = (float)(rand() % 4000 - 2000);
			mine_controller->spawn_position.YValue = (float)(rand() % 2000 - 1000);

			// If near player.
			if (mine_controller->IsNearPosition(this->player_transform.lock()->position, 200))
				continue;

			// If near boss.
			if (mine_controller->IsNearPosition(this->GetGameObject()->GetComponent<Component_Transform>()->position, 200))
				continue;

			break;
		}

		Scene::Instantiate(mine);
		this->mines.push_back(mine);
	}

	AudioPlayer::GetInstance().PlayAudioClip(AUDIO_MINES_SPAWN, 70);
}

void Component_BossController::ChangeState(std::shared_ptr<BossState> state) {
	this->current_state = state;
}

void Component_BossController::GetDamaged(int damage) {
	this->health -= damage;
	
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("boss hurt");
	AudioPlayer::GetInstance().PlayAudioClip(AUDIO_BOSS_HURT, 75);
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false;

	if (this->health <= 0)
		this->Explode();
}

void Component_BossController::Explode() {
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false; // Hide sprite.
	this->GetGameObject()->GetComponent<Component_BossCollider>()->is_active = false; // Disable collision.
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("boss explosion");
	AudioPlayer::GetInstance().PlayAudioClip(AUDIO_BOSS_EXPLOSION);
	this->DespawnHomingMissiles();
	this->DespawnMines();

	this->ChangeState(this->state_exploding);
}

void Component_BossController::DespawnHomingMissiles() {
	for (auto homing_missile : this->homing_missiles)
		if (!homing_missile.expired() && homing_missile.lock()->HasComponent<Component_HomingMissileController>())
			homing_missile.lock()->GetComponent<Component_HomingMissileController>()->Explode();
}

void Component_BossController::DespawnMines() {
	for (auto mine : this->mines)
		if (!mine.expired() && mine.lock()->HasComponent<Component_MineController>())
			mine.lock()->GetComponent<Component_MineController>()->Explode();
}
