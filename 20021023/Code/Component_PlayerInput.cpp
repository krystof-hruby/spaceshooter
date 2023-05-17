// Component_PlayerInput.cpp
// Krystof Hruby
// 2023

#include "Component_PlayerInput.h"

short Component_PlayerInput::GetInput_Rotation() {
	if (this->KeyPressed(DIK_A) || this->KeyPressed(DIK_LEFT))
		return INPUT_LEFT;

	if (this->KeyPressed(DIK_D) || this->KeyPressed(DIK_RIGHT))
		return INPUT_RIGHT;

	return INPUT_NONE;
}

short Component_PlayerInput::GetInput_Movement() {
	if (this->KeyPressed(DIK_S) || this->KeyPressed(DIK_DOWN))
		return INPUT_BACKWARD;

	if (this->KeyPressed(DIK_W) || this->KeyPressed(DIK_UP))
		return INPUT_FORWARD;

	return INPUT_NONE;
}

bool Component_PlayerInput::GetInput_Shooting() {
	return this->KeyPressed(DIK_SPACE);
}
