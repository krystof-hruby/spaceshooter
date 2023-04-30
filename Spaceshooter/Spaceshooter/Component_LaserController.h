// Component_LaserController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"

class Component_LaserController : public Component {
public:
	using Component::Component;
	inline bool Startable() const override { return false; }
	void Update() override;
	float laser_period = 1;

private:
	float laser_time = 0;
};

