// Component_RectangleCollider.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"

class Component_RectangleCollider : public Component {

public:
	Component_RectangleCollider(std::shared_ptr<GameObject> game_object);

	void Start();
	void Update();
};

