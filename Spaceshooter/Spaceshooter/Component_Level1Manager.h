// Component_Level1Manager.h
// Krystof Hruby
// 2023

#pragma once

#include "Level1Phase.h"
#include "Level1Phase_Gameplay.h"
#include "Level1Phase_Preparation.h"
#include "Level1Phase_Tutorial.h"
#include "Component.h"
#include "Component_BackgroundController.h"
#include "ComponentRegistry.h"
#include "ScoreManager.h"

class Component_Level1Manager : public Component, public std::enable_shared_from_this<Component_Level1Manager> {
public:
	using Component::Component;
	void Start() override;
	void Update() override;

	float fade_in_period = 1;
	float commander_ui_spawn_period = 1;
	float preparation_period = 1;

	std::weak_ptr<ComponentRegistry> component_registry;
	std::weak_ptr<Component_BackgroundController> background_controller;
	std::weak_ptr<GameObject> commander_ui;
	std::weak_ptr<GameObject> text_ui;
	std::shared_ptr<ScoreManager> score_manager = std::make_shared<ScoreManager>();
	
	
	float level_start_period = 1;
	float level_end_period = 1;
	float fade_out_period = 1;

private:
	// For phases.
	friend class Level1Phase_Preparation;
	friend class Level1Phase_Tutorial;
	friend class Level1Phase_Gameplay;

	std::shared_ptr<Level1Phase> current_phase;
	void ChangePhase(std::shared_ptr<Level1Phase> phase);

	// Phases:
	std::shared_ptr<Level1Phase_Preparation> phase_preparation = std::make_shared<Level1Phase_Preparation>();
	std::shared_ptr<Level1Phase_Tutorial> phase_tutorial = std::make_shared<Level1Phase_Tutorial>();
	std::shared_ptr<Level1Phase_Gameplay> phase_gameplay = std::make_shared<Level1Phase_Gameplay>();
};

