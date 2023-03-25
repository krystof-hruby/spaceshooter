// SceneManager.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>

#include "Scene.h"

// Manages scenes.
class SceneManager final {
private:
	// Singleton
	SceneManager() { }
	SceneManager(SceneManager const& copy) = delete;
	SceneManager operator = (SceneManager const& copy) = delete;
	
	std::shared_ptr<Scene> current_scene;

public:
	// Returns singleton instance.
	static SceneManager& GetInstance();
	
	// Ends current game scene. Starts new game scene and marks it as current to be updated.
	void ChangeScene(std::shared_ptr<Scene> scene);

	// Returns the currently played game scene.
	std::shared_ptr<Scene> GetCurrentScene() const;
};

