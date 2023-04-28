// Component_BossController.h
// Krystof Hruby
// 2023

#pragma once

#include <vector>
#include "Component_Transform.h"

class Component_BossController final : public Component {
private:
	std::vector<std::weak_ptr<GameObject>> homing_missiles;
	std::vector<std::weak_ptr<GameObject>> lasers;
	float grace_period_time = 0;
	float laser_shoot_time = 0;
	float homing_missile_shoot_time = 0;
	bool dead = false;
	bool spawning = true;

public:
	using Component::Component;

	std::weak_ptr<Component_Transform> player_transform;
	Vector2D spawn_position;
	Vector2D spawn_target;
	int health = 1;
	float movement_speed = 1;
	float grace_period = 1;
	float lasers_shoot_period = 1;
	float homing_missile_shoot_period = 1;
	Vector2D homing_missile_spawn_offset;

	void Spawn();
	void GetDamaged(int damage);
	void ShootLasers();
	void ShootHomingMissile();
	void Explode();
	void DespawnHomingMissiles();
	void Start() override;
	void Update() override;
};

