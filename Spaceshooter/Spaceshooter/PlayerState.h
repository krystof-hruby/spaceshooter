// PlayerState.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>

class Component_PlayerController;

// Abstract parent class for player states. Override methods to provide functionality.
class PlayerState {
public:
	virtual void Play(std::shared_ptr<Component_PlayerController> player_controller) { }

protected:
	PlayerState() { }
};

