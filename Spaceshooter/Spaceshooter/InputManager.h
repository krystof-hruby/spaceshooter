// InputManager.h
// Krystof Hruby
// 2023

#pragma once

#include "myinputs.h" // Expose all the key definitions

// Format of all keys is: DIK_[key_name] (e.g. DIK_W, DIK_0, DIK_LSHIFT, DIK_UP) (from shell).
typedef unsigned char KEYBOARD_KEY;

// Samples keyboard and gets input from it when requested.
class InputManager final {
private:
	// Singleton
	InputManager() { }
	InputManager(InputManager const& copy) = delete;
	InputManager operator = (InputManager const& copy) = delete;

public:
	// Returns singleton instance.
	static InputManager& GetInstance();

	// Was key pressed.
	bool KeyPressed(KEYBOARD_KEY key) const;

	// Samples the keyboard. Called every frame in gameloop; other calls are unnecessary, but do not break.
	void Update() const;
};

