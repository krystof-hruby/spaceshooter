// Component_BackgroundController.cpp
// Krystof Hruby
// 2023

#include "Component_BackgroundController.h"

#include "Component_SpriteRenderer.h"
#include "GameObject.h"
#include "Time.h"

void Component_BackgroundController::Start() {
	this->GetGameObject()->GetComponent<Component_SpriteRenderer>()->transparency = 1;
	this->FadeIn();
}

void Component_BackgroundController::Update() {
	if (this->fading_in) {
		auto sprite_renderer = this->GetGameObject()->GetComponent<Component_SpriteRenderer>();
		
		sprite_renderer->transparency -= (float)Time::delta_time;

		// Could go under.
		if (sprite_renderer->transparency <= 0) {
			this->fading_in = false;
			sprite_renderer->transparency = 0;
		}
	}

	if (this->fading_out) {
		auto sprite_renderer = this->GetGameObject()->GetComponent<Component_SpriteRenderer>();
		
		sprite_renderer->transparency += (float)Time::delta_time;

		// Could go over.
		if (sprite_renderer->transparency >= 1) {
			this->fading_out = false;
			sprite_renderer->transparency = 1;
		}
	}
}

void Component_BackgroundController::FadeIn() {
	if (this->fading_in)
		return;

	this->fading_in = true;
}

void Component_BackgroundController::FadeOut() {
	if (this->fading_out)
		return;
	
	this->fading_out = true;
}
