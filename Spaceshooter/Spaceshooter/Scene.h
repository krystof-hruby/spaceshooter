// Scene.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>
#include <vector>

#include "ComponentRegistry.h"
#include "Identifiable.h"
#include "MainCamera.h"

// Holds and controls game objects.
class Scene : public Identifiable {
protected:
	Scene();
	
	std::shared_ptr<ComponentRegistry> component_registry = std::make_shared<ComponentRegistry>();
	std::vector<std::shared_ptr<GameObject>> scene_objects;
	MainCamera camera;

	// Stops any currently playing sounds.
	void StopAllSounds() const;
public:
	// Called after Load().
	void Components_Start() const;
	// Called after Update().
	void Components_Update() const;

	// Updates component registry (unregisters all components marked to be unregistered).
	// Must be called between frames (after update) to avoid iteration errors.
	void UpdateComponentRegistry() const;

	// Called when changed to this scene.
	virtual void Load();
	// Called every frame while being current scene.
	virtual void Update();
	// Called when changed from this scene to other scene.
	virtual void Unload();

	// Instantiates this object in the current scene.
	static void Instantiate(std::shared_ptr<GameObject> game_object);
};
