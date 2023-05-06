// Component_Level1Manager.h
// Krystof Hruby
// 2023

#pragma once

#include "Level1Phases.h"
#include "Component.h"
#include "Component_Animator.h"
#include "Component_BackgroundController.h"
#include "Component_UIController.h"
#include "ComponentRegistry.h"

class Component_Level1Manager : public Component, public std::enable_shared_from_this<Component_Level1Manager> {
public:
	using Component::Component;
	void Start() override;
	void Update() override;

	float fade_in_period = 1;
	float commander_ui_spawn_period = 1;
	float preparation_period = 1;
	float player_spawn_period = 1;
	float asteroids_spawn_period = 1;
	float level_length;

	std::weak_ptr<ComponentRegistry> component_registry;
	std::weak_ptr<Component_BackgroundController> background_controller;
	std::weak_ptr<Component_UIController> ui_controller;
	
private:
	// For phases.
	friend class Level1Phase_Preparation;
	friend class Level1Phase_Intro;
	friend class Level1Phase_Tutorial;
	friend class Level1Phase_Gameplay;
	friend class Level1Phase_Outro;

	std::shared_ptr<Level1Phase> current_phase;
	void ChangePhase(std::shared_ptr<Level1Phase> phase);

	// Phases:
	std::shared_ptr<Level1Phase_Preparation> phase_preparation = std::make_shared<Level1Phase_Preparation>();
	std::shared_ptr<Level1Phase_Intro> phase_intro = std::make_shared<Level1Phase_Intro>();
	std::shared_ptr<Level1Phase_Tutorial> phase_tutorial = std::make_shared<Level1Phase_Tutorial>();
	std::shared_ptr<Level1Phase_Gameplay> phase_gameplay = std::make_shared<Level1Phase_Gameplay>();
	std::shared_ptr<Level1Phase_Outro> phase_outro = std::make_shared<Level1Phase_Outro>();
};

