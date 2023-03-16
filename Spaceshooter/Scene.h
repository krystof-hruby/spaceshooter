// Scene.h
// Krystof Hruby
// 2023

#pragma once

#include <string>

#include "UUID.h"

class Scene {
private:
	UUID id;

public:
	virtual void Load() = 0;
	virtual void Update() = 0;
	virtual void Unload() = 0;

	UUID GetID();
};
