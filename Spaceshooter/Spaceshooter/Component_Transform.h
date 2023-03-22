// Component_Transform.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "vector2D.h"

// Provides position, rotation, and scale.
class Component_Transform : public Component {
public:
	using Component::Component;
	
	Vector2D position;
	float rotation = 0;
	float scale = 1;
};
