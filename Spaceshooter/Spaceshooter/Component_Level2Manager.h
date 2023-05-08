// Component_Level2Manager.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"

class Component_Level2Manager : public Component {
public:
	using Component::Component;
	void Start() override;
	void Update() override;

	float level_end_period = 1;
	float fade_out_period = 1;

private:
	float level_end_time = 0;
};

