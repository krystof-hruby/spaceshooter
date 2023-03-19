// Scene.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>

#include "Identifiable.h"
#include "ComponentRegistry.h"

class Scene : public Identifiable {
protected:
	Scene();
	std::shared_ptr<ComponentRegistry> component_registry = std::make_shared<ComponentRegistry>();

public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;
};
