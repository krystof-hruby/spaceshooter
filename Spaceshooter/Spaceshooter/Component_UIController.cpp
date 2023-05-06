// Component_UIController.cpp
// Krystof Hruby
// 2023

// This whole code is kind of a mess, but I could not be bothered to write another several state machines.
// They take too much time and space.
// Animations should probably get a whole animation engine.

#include "Component_UIController.h"

#include "GameObject.h"
#include "Time.h"

void Component_UIController::Start() {
	this->animator_commander_ui = this->commander_ui.lock()->GetComponent<Component_Animator>();
	this->transform_commander_ui = this->commander_ui.lock()->GetComponent<Component_Transform>();
	this->animator_text_ui = this->text_ui.lock()->GetComponent<Component_Animator>();
}

void Component_UIController::Update() {
	if (this->current_level == 1)
		this->Update_Level1();
}

void Component_UIController::SpawnCommanderFrame() {
	this->transform_commander_ui.lock()->scale += (float)Time::delta_time * 15;

	if (this->transform_commander_ui.lock()->scale >= 0.4f)
		this->transform_commander_ui.lock()->scale = 0.4f;
}

void Component_UIController::DespawnCommanderFrame() {
	this->transform_commander_ui.lock()->scale -= (float)Time::delta_time * 15;

	if (this->transform_commander_ui.lock()->scale <= 0)
		this->transform_commander_ui.lock()->scale = 0;
}

void Component_UIController::PlayLevel1IntroAndTutorial() {
	this->animator_commander_ui.lock()->PlayAnimation("commander spawn");
	this->started_level1_intro = true;
}

void Component_UIController::PlayLevel1Cutscene1() {
	this->animator_commander_ui.lock()->PlayAnimation("commander spawn");
	this->play_level1_cutscene1 = true;
}

void Component_UIController::PlayLevel1Cutscene2() {
	this->animator_commander_ui.lock()->PlayAnimation("commander spawn");
	this->play_level1_cutscene2 = true;
}

void Component_UIController::PlayLevel1Cutscene3() {
	this->animator_commander_ui.lock()->PlayAnimation("commander spawn");
	this->play_level1_cutscene3 = true;
}

void Component_UIController::PlayLevel1Outro() {
}

void Component_UIController::Update_Level1() {
	if (this->started_level1_intro && !this->finished_level1_tutorial) {
		if (!this->commander_talking && this->animator_commander_ui.lock()->AnimationFinished("commander spawn")) {
			this->animator_commander_ui.lock()->PlayAnimation("commander talk");
			this->animator_text_ui.lock()->PlayAnimation("text level 1 intro");
			this->commander_talking = true;
		}
		else if (!this->finished_level1_intro && this->animator_text_ui.lock()->AnimationFinished("text level 1 intro")) {
			this->animator_text_ui.lock()->PlayAnimation("text tutorial");
			this->finished_level1_intro = true;
		}
		else if (!this->finished_level1_tutorial && this->animator_text_ui.lock()->AnimationFinished("text tutorial")) {
			this->animator_commander_ui.lock()->PlayAnimation("commander despawn");
			this->finished_level1_tutorial = true;
			this->commander_talking = false;
		}
	}

	if (this->play_level1_cutscene1) {
		if (!this->commander_talking && this->animator_commander_ui.lock()->AnimationFinished("commander spawn")) {
			this->animator_commander_ui.lock()->PlayAnimation("commander talk");
			this->animator_text_ui.lock()->PlayAnimation("text level 1 cutscene 1");
			this->commander_talking = true;
		}
		else if (this->animator_text_ui.lock()->AnimationFinished("text level 1 cutscene 1")) {
			this->animator_commander_ui.lock()->PlayAnimation("commander despawn");
			this->commander_talking = false;
			this->play_level1_cutscene1 = false;
		}
	}

	if (this->play_level1_cutscene2) {
		if (!this->commander_talking && this->animator_commander_ui.lock()->AnimationFinished("commander spawn")) {
			this->animator_commander_ui.lock()->PlayAnimation("commander talk");
			this->animator_text_ui.lock()->PlayAnimation("text level 1 cutscene 2");
			this->commander_talking = true;
		}
		else if (this->animator_text_ui.lock()->AnimationFinished("text level 1 cutscene 2")) {
			this->animator_commander_ui.lock()->PlayAnimation("commander despawn");
			this->commander_talking = false;
			this->play_level1_cutscene1 = false;
		}
	}

	if (this->play_level1_cutscene3) {
		if (!this->commander_talking && this->animator_commander_ui.lock()->AnimationFinished("commander spawn")) {
			this->animator_commander_ui.lock()->PlayAnimation("commander talk");
			this->animator_text_ui.lock()->PlayAnimation("text level 1 cutscene 3");
			this->commander_talking = true;
		}
		else if (this->animator_text_ui.lock()->AnimationFinished("text level 1 cutscene 3")) {
			this->animator_commander_ui.lock()->PlayAnimation("commander despawn");
			this->commander_talking = false;
			this->play_level1_cutscene1 = false;
		}
	}
}

