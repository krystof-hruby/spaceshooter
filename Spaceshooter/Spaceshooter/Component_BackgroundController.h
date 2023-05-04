// Component_BackgroundController.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"

class Component_BackgroundController : public Component {
public:
	using Component::Component;
	void Start() override;
	void Update() override;

	void FadeIn();
	void FadeOut();

private:
	bool fading_in = false;
	bool fading_out = false;
};

