// Component_EnemyShipController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"

class Component_EnemyShipController final : public Component {
private:

public:
	using Component::Component;

	void Update() override;
};

