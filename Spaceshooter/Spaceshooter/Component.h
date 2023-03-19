// Component.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>

#include "Identifiable.h"

class GameObject;

// Base class for all components.
class Component : public Identifiable {
protected:
	Component(std::shared_ptr<GameObject> game_object);
	std::shared_ptr<GameObject> game_object;

public:
	// Returns the game object which has this component.
	std::shared_ptr<GameObject> GetGameObject();

	// Called once at the start of a level.
	virtual void Start();
	
	// Called once every frame.
	virtual void Update();
};

