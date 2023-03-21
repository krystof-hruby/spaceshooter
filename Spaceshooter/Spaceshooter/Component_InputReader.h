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
	using Component::Component;

	bool KeyPressed(KEY key);
};

