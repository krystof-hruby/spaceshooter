// Component_Level1Manager.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "Component_BackgroundController.h"
#include "Component_SpriteRenderer.h"
#include "ScoreManager.h"

class Component_Level1Manager : public Component {
public:
	using Component::Component;
	void Start() override;
	void Update() override;

	std::weak_ptr<Component_BackgroundController> background_controller;
	std::shared_ptr<ScoreManager> score_manager = std::make_shared<ScoreManager>();
	float level_end_period = 1;
	float fade_out_period = 1;

private:
	float level_end_time = 0;
};

