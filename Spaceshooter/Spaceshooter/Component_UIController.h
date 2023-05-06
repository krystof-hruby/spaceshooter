// Component_UIController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "Component_Animator.h"
#include "Component_Transform.h"

class Component_UIController : public Component {
public:
	using Component::Component;
	void Start() override;
	void Update() override;

	std::weak_ptr<GameObject> commander_ui;
	std::weak_ptr<GameObject> text_ui;

	void SpawnCommanderFrame();
	void DespawnCommanderFrame();

	// Level 1:
	void PlayLevel1IntroAndTutorial();
	bool Level1IntroFinished() { return this->finished_level1_intro; }
	bool Level1TutorialFinished() { return this->finished_level1_tutorial; }

	void PlayLevel1Cutscene1();
	
	void PlayLevel1Cutscene2();
	
	void PlayLevel1Cutscene3();
	
	void PlayLevel1Outro();

	// Level 2:

private:
	std::weak_ptr<Component_Animator> animator_commander_ui;
	std::weak_ptr<Component_Animator> animator_text_ui;
	std::weak_ptr<Component_Transform> transform_commander_ui;

	bool commander_talking = false;
	int current_level = 1;

	// Level 1:
	bool started_level1_intro = false;
	bool finished_level1_intro = false;
	bool finished_level1_tutorial = false;

	bool play_level1_cutscene1 = false;
	bool play_level1_cutscene2 = false;
	bool play_level1_cutscene3 = false;

	void Update_Level1();

	// Level 2:
};

