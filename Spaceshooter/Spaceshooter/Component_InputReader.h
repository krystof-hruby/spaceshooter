// Component_InputReader.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "InputManager.h"

// Allows this component to get input from InputManager.
class Component_InputReader final : public Component {
public:
	using Component::Component;
	
	inline bool Updatable() override { return false; }

	// Checks if key was pressed.
	// Format of all keys is: DIK_[key_name] (e.g. DIK_W, DIK_0, DIK_LSHIFT, DIK_UP) (from shell).
	inline bool KeyPressed(KEYBOARD_KEY key) { return InputManager::GetInstance().KeyPressed(key); }
};

