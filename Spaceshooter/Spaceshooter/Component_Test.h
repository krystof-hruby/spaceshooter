// Component_Test.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"

// Component for testing.
class Component_Test : public Component {
public:
	using Component::Component;

	void Start();
	void Update();
};

