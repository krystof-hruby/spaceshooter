// InputManager.cpp
// Krystof Hruby
// 2023

#include "InputManager.h"

InputManager& InputManager::GetInstance() {
	static InputManager instance;
	return instance;
}

bool InputManager::KeyPressed(KEYBOARD_KEY key) const {
	return MyInputs::GetInstance()->KeyPressed(key);
}

void InputManager::Update() const {
	// Updates keyboard state.
	MyInputs::GetInstance()->SampleKeyboard();
}