// Component_InputReader.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "InputManager.h"

// Allows this component to get input from InputManager.
// Can be overriden for more game-specific functionality.
class Component_InputReader : public Component {
public:
	using Component::Component;
	
	// Override and set to true if this component starts. Currently: saves performance by ignoring Start function of this component type.
	inline virtual bool Startable() const override { return false; }

	// Override and set to true if this component updates. Currently: saves performance by ignoring Update function of this component type.
	inline virtual bool Updatable() const override { return false; }

	// Checks if key was pressed.
	// Format of all keys is: DIK_[key_name] (e.g. DIK_W, DIK_0, DIK_LSHIFT, DIK_UP) (from shell).
	inline bool KeyPressed(KEYBOARD_KEY key) { return InputManager::GetInstance().KeyPressed(key); }
};

