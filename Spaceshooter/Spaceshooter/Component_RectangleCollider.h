// Component_RectangleCollider.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"

class Component_RectangleCollider : public Component {

public:
	using Component::Component;

	void Start();
	void Update();
};

