// Component_PlayerInput.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_InputReader.h"

const int INPUT_NONE = 0;
const int INPUT_LEFT = -1;
const int INPUT_RIGHT = 1;
const int INPUT_FORWARD = 1;
const int INPUT_BACKWARD = -1;

// Gets input controlling player spaceship.
class Component_PlayerInput final : public Component_InputReader {
public:
	using Component_InputReader::Component_InputReader;

	// LEFT - RIGHT.
	short GetInput_Rotation();

	// FORWARD - BACKWARD.
	short GetInput_Movement();

	// Spacebar.
	bool GetInput_Shooting();
};

