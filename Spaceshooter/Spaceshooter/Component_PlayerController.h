// Component_PlayerController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_Level1Manager.h"
#include "Component_Level2Manager.h"
#include "Component_Level3Manager.h"
#include "PlayerState.h"
#include "PlayerState_Despawning.h"
#include "PlayerState_Exploding.h"
#include "PlayerState_Flying.h"
#include "PlayerState_Spawning.h"

// Controls the player spaceship.
class Component_PlayerController final : public Component, public std::enable_shared_from_this<Component_PlayerController> {
public:
	using Component::Component;
	void Start() override;
	void Update() override;

	float movement_speed = 1;
	float rotation_speed = 1;
	float reload_period = 1;

	std::weak_ptr<Component_Level1Manager> level1manager;
	std::weak_ptr<Component_Level2Manager> level2manager;
	std::weak_ptr<Component_Level3Manager> level3manager;

	void Explode();
	void Despawn();

private:
	// For states.
	friend class PlayerState_Spawning;
	friend class PlayerState_Flying;
	friend class PlayerState_Exploding;
	friend class PlayerState_Despawning;

	std::shared_ptr<PlayerState> current_state;
	void ChangeState(std::shared_ptr<PlayerState> player_state);
	
	// States:
	std::shared_ptr<PlayerState_Spawning> state_spawning = std::make_shared<PlayerState_Spawning>();
	std::shared_ptr<PlayerState_Flying> state_flying = std::make_shared<PlayerState_Flying>();
	std::shared_ptr<PlayerState_Exploding> state_exploding = std::make_shared<PlayerState_Exploding>();
	std::shared_ptr<PlayerState_Despawning> state_despawning = std::make_shared<PlayerState_Despawning>();

	void ShootBullet(Vector2D position, float rotation, Vector2D direction);
};

