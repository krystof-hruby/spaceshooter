// Component_PlayerInput.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_InputReader.h"

#define INPUT_NONE 0
#define INPUT_LEFT -1
#define INPUT_RIGHT 1
#define INPUT_FORWARD 1
#define INPUT_BACKWARD -1

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

