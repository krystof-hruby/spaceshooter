// Component_PlayerController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_ScoreManager.h"
#include "PlayerState.h"
#include "PlayerState_Despawning.h"
#include "PlayerState_Exploding.h"
#include "PlayerState_Flying.h"
#include "PlayerState_GracePeriod.h"
#include "PlayerState_Spawning.h"
#include "vector2D.h"

class Component_PlayerController final : public Component, public std::enable_shared_from_this<Component_PlayerController> {
public:
	using Component::Component;
	void Start() override;
	void Update() override;

	std::weak_ptr<Component_ScoreManager> score_manager;
	float movement_speed = 1;
	float rotation_speed = 1;
	float grace_period = 1;
	float reload_period = 1;
	float free_roaming_period = 1;

	void ChangeState(std::shared_ptr<PlayerState> player_state);
	void Explode();
	void Despawn();
	bool Despawned() const { return this->despawned; }

private:
	// For states.
	friend class PlayerState_GracePeriod;
	friend class PlayerState_Spawning;
	friend class PlayerState_Flying;
	friend class PlayerState_Exploding;
	friend class PlayerState_Despawning;

	std::shared_ptr<PlayerState> current_state;
	
	// States:
	std::shared_ptr<PlayerState_GracePeriod> state_grace_period = std::make_shared<PlayerState_GracePeriod>();
	std::shared_ptr<PlayerState_Spawning> state_spawning = std::make_shared<PlayerState_Spawning>();
	std::shared_ptr<PlayerState_Flying> state_flying = std::make_shared<PlayerState_Flying>();
	std::shared_ptr<PlayerState_Exploding> state_exploding = std::make_shared<PlayerState_Exploding>();
	std::shared_ptr<PlayerState_Despawning> state_despawning = std::make_shared<PlayerState_Despawning>();

	bool despawned = false;
	void ShootBullet(Vector2D position, float rotation, Vector2D direction);
};

