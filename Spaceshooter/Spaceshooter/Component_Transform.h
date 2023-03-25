// Component_Transform.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "vector2D.h"

// Provides position, rotation, and scale.
class Component_Transform final : public Component {
public:
	using Component::Component;
	
	inline bool Startable() const override { return false; }
	inline bool Updatable() const override { return false; }

	Vector2D position;
	float rotation = 0;
	float scale = 1;
};

