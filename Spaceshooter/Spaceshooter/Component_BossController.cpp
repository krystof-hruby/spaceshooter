// Component_BossController.cpp
// Krystof Hruby
// 2023

#include "Component_BossController.h"

#include "ActiveBounds.h"
#include "Component_Animator.h"
#include "Component_BossCollider.h"
#include "Component_HomingMissileController.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Scene.h"
#include "Time.h"

#include "Logging.h" // TODO: remove

void Component_BossController::Start() {
	this->GetGameObject()->GetComponent<Component_Transform>()->position = this->spawn_position;
}

void Component_BossController::Update() {
	auto transform = this->GetGameObject()->GetComponent<Component_Transform>();
	auto sprite_renderer = this->GetGameObject()->GetComponent<Component_SpriteRenderer>();
	auto animator = this->GetGameObject()->GetComponent<Component_Animator>();

	if (animator->AnimationFinished("boss explosion") || !ActiveBounds::IsInBounds(transform->position)) {
		// Was eliminated.
		this->GetGameObject()->Destroy();

		// TODO: display end screen

		return;
	}

	if (this->spawning) {
		this->Spawn();
		return;
	}

	// Spawn lasers and homing missiles.
	this->grace_period_time += (float)Time::delta_time;
	this->laser_shoot_time += (float)Time::delta_time;
	this->homing_missile_shoot_time += (float)Time::delta_time;

	if (!this->dead && this->grace_period_time > this->grace_period) {
		if (this->laser_shoot_time > this->lasers_shoot_period)
			this->ShootLasers();

		if (this->homing_missile_shoot_time > this->homing_missile_shoot_period)
			this->ShootHomingMissile();
	}

	// Floating movement.
	this->floating_time += (float)Time::delta_time;
	transform->position.XValue = this->spawn_target.XValue + (sin(this->floating_time * 2) * this->floating_movement_speed);
	transform->position.YValue = this->spawn_target.YValue + (sin(this->floating_time * 1) * this->floating_movement_speed);
}

void Component_BossController::GetDamaged(int damage) {
	this->health -= damage;

	if (this->health <= 0)
		this->Explode();
}

void Component_BossController::Spawn() {
	auto transform = this->GetGameObject()->GetComponent<Component_Transform>();

	// Interpolate between this position and spawn position.
	float time_step = (float)Time::delta_time * this->movement_speed;
	transform->position.XValue = (1 - time_step) * transform->position.XValue + time_step * this->spawn_target.XValue;
	transform->position.YValue = (1 - time_step) * transform->position.YValue + time_step * this->spawn_target.YValue;

	// Check if it is near spawn target to avoid weird sprite rendering effects.
	if ((transform->position.XValue >= this->spawn_target.XValue - 30 && transform->position.XValue <= this->spawn_target.XValue + 30) && (transform->position.YValue >= this->spawn_target.YValue - 30 && transform->position.YValue <= this->spawn_target.YValue + 30)) {
		this->spawn_target = transform->position; // Update spawn target to current position (is slightly different).
		this->spawning = false;
	}
}

void Component_BossController::ShootLasers() {
	// TODO:
	this->laser_shoot_time = 0;
}

void Component_BossController::ShootHomingMissile() {
	return; // TODO:

	std::shared_ptr<GameObject> homing_missile = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::HomingMissile, this->GetGameObject()->GetComponentRegistry());
	homing_missile->GetComponent<Component_HomingMissileController>()->player_transform = this->player_transform;
	homing_missile->GetComponent<Component_Transform>()->position = this->GetGameObject()->GetComponent<Component_Transform>()->position - this->homing_missile_spawn_offset;

	Scene::Instantiate(homing_missile);
	this->homing_missiles.push_back(homing_missile);
	this->homing_missile_shoot_time = 0;
}

void Component_BossController::Explode() {
	if (this->dead)
		return; // Should not happen but just in case.

	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->is_active = false; // Hide sprite.
	this->GetGameObject()->GetComponent<Component_BossCollider>()->is_active = false; // Disable collision.
	this->GetGameObject()->GetComponent<Component_Animator>()->PlayAnimation("boss explosion");
	this->DespawnHomingMissiles();
	this->dead = true;
}

void Component_BossController::DespawnHomingMissiles() {
	for (auto homing_missile : this->homing_missiles)
		if (!homing_missile.expired() && homing_missile.lock()->HasComponent<Component_HomingMissileController>())
			homing_missile.lock()->GetComponent<Component_HomingMissileController>()->Explode();
}
