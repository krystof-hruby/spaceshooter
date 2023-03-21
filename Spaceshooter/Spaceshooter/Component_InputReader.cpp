// Component_IntputReader.cpp
// Krystof Hruby
// 2023

#include "Component_InputReader.h"

Component_InputReader::Component_InputReader(std::shared_ptr<GameObject> game_object) : Component(game_object) { }

bool Component_InputReader::KeyPressed(KEY key) {
	// Updates currently pressed keys
	MyInputs::GetInstance()->SampleKeyboard();
	
	return MyInputs::GetInstance()->KeyPressed(key);
}

void Component_InputReader::Start() { }

void Component_InputReader::Update() { }
