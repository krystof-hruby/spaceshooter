// Scene.h
// Krystof Hruby
// 2023

#pragma once

#include "Identifiable.h"

class Scene : public Identifiable {
public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;
};
