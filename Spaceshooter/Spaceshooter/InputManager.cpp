// InputManager.cpp
// Krystof Hruby
// 2023

#include "InputManager.h"

InputManager& InputManager::GetInstance() {
	static InputManager instance;
	return instance;
}

bool InputManager::KeyPressed(KEYBOARD_KEY key) {
	return MyInputs::GetInstance()->KeyPressed(key);
}

void InputManager::Update() {
	// Updates keyboard state.
	MyInputs::GetInstance()->SampleKeyboard();
}