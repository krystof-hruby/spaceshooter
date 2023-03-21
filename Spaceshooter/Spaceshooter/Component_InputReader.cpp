// Component_IntputReader.cpp
// Krystof Hruby
// 2023

#include "Component_InputReader.h"

bool Component_InputReader::KeyPressed(KEY key) {
	// Updates currently pressed keys
	MyInputs::GetInstance()->SampleKeyboard();
	
	return MyInputs::GetInstance()->KeyPressed(key);
}
