// Component_BossController.h
// Krystof Hruby
// 2023

#pragma once

#include <unordered_map>
#include <vector>
#include "BossState_Exploding.h"
#include "BossState_Floating.h"
#include "BossState_GracePeriod.h"
#include "BossState_MovingToFloatingSpot.h"
#include "Component_Transform.h"

// Controls the boss through state machine.
class Component_BossController final : public Component, public std::enable_shared_from_this<Component_BossController> {
public:
	using Component::Component;
	void Start() override;
	void Update() override;
	
	std::weak_ptr<Component_Transform> player_transform;
	Vector2D spawn_position;
	std::vector<Vector2D> floating_spots;
	int health = 1;
	float movement_speed = 1;
	float floating_movement_speed = 1;
	float grace_period = 1;
	float moving_to_floating_spot_period = 1;
	float attack_period = 1;
	Vector2D homing_missile_spawn_offset;
	int number_of_mines = 1;

	void ChangeState(std::shared_ptr<BossState> state);
	void ShootHomingMissile();
	void SpawnMines();
	void GetDamaged(int damage);
	void Explode();

private:
	// For states.
	friend class BossState_GracePeriod;
	friend class BossState_MovingToFloatingSpot;
	friend class BossState_Floating;
	friend class BossState_Exploding;

	std::shared_ptr<BossState> current_state;

	// States:
	std::shared_ptr<BossState_GracePeriod> state_grace_period = std::make_shared<BossState_GracePeriod>();
	std::shared_ptr<BossState_MovingToFloatingSpot> state_movig_to_floating_spot = std::make_shared<BossState_MovingToFloatingSpot>();
	std::shared_ptr<BossState_Floating> state_floating = std::make_shared<BossState_Floating>();
	std::shared_ptr<BossState_Exploding> state_exploding = std::make_shared<BossState_Exploding>();

	Vector2D current_floating_spot;
	std::vector<std::weak_ptr<GameObject>> homing_missiles;
	std::vector<std::weak_ptr<GameObject>> mines;

	void DespawnHomingMissiles();
	void DespawnMines();
};

