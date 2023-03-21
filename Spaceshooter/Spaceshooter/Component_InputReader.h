// Component_IntputReader.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"

#include "myinputs.h" // Expose all the key definitions

typedef unsigned char KEY;

// Enables reading keyboard input.
class Component_InputReader : public Component {
public:
	Component_InputReader(std::shared_ptr<GameObject> game_object);

	bool KeyPressed(KEY key);
	void Start();
	void Update();
};

