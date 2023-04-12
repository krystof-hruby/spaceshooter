// Component.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>

#include "Identifiable.h"

class GameObject; // Forward class declaration to avoid circular includes. Must #include "GameObject.h" in .cpp file if needs to access GameObject methods.

// Base class for all components.
class Component : public Identifiable {
private:
	// Game object that owns this component.
	// Weak pointer to avoid circular references.
	std::weak_ptr<GameObject> game_object;

public:
	// ALWAYS call this constructor ONLY from derived classes. Will break very badly otherwise.
	Component(std::shared_ptr<GameObject> game_object);

	// Whether to start and update the component.
	bool is_active = true;

	// Override and set to false if this component never starts. Saves performance by ignoring Start function of this component type.
	inline virtual bool Startable() const { return true; }
	
	// Override and set to false if this component never updates. Saves performance by ignoring Update function of this component type.
	inline virtual bool Updatable() const { return true; }

	// Returns the game object which has this component.
	std::shared_ptr<GameObject> GetGameObject();

	// Called once at the start of a level.
	virtual void Start();
	
	// Called once every frame.
	virtual void Update();
};

