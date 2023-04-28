// Scene.h
// Krystof Hruby
// 2023

#pragma once

#include "ComponentRegistry.h"
#include "MainCamera.h"

// Holds and controls game objects.
class Scene : public Identifiable {
public:
	// Called when changed to this scene.
	virtual void Load();

	// Called every frame while being current scene.
	virtual void Update();

	// Called when changed from this scene to other scene.
	virtual void Unload();

	// Instantiates this object in the current scene.
	static void Instantiate(std::shared_ptr<GameObject> game_object);

protected:
	Scene();
	
	std::shared_ptr<ComponentRegistry> component_registry = std::make_shared<ComponentRegistry>();
	MainCamera camera;

	// Stops any currently playing sounds.
	void StopAllSounds() const;

private:
	// For Components_Update and UpdateComponentRegistry.
	friend class Gameloop;

	// Updates components and components registry.
	// Must be called between frames, after Scene::Update.
	void Components_Update() const;

	// Must hold references to all game_objects to keep pointers alive.
	std::vector<std::shared_ptr<GameObject>> scene_objects;
};
