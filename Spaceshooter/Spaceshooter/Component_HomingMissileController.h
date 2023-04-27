// Component_HomingMissileController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "Component_Transform.h"

class Component_HomingMissileController final : public Component {
private:

public:
	using Component::Component;

	std::weak_ptr<Component_Transform> player_transform;
	float movement_speed = 1;

	void Explode();
	inline bool Startable() const override { return false; }
	void Update() override;
};

