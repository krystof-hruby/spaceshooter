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
	Scene();
	std::shared_ptr<ComponentRegistry> component_registry = std::make_shared<ComponentRegistry>();

	// Stops any currently playing sounds.
	void StopAllSounds();
public:
	// Called after Load().
	void Components_Start();
	// Called after Update().
	void Components_Update();

	// Called when changed to this scene.
	virtual void Load();
	// Called every frame while being current scene.
	virtual void Update();
	// Called when changed from this scene to other scene.
	virtual void Unload();
};
