// Scene.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>

#include "Identifiable.h"
#include "ComponentRegistry.h"

// Holds and controls game objects.
class Scene : public Identifiable {
protected:
	Scene() { }
	std::shared_ptr<ComponentRegistry> component_registry = std::make_shared<ComponentRegistry>();

public:
	virtual void Load() = 0;
	virtual void Update() = 0;
	virtual void Unload() = 0;
};
