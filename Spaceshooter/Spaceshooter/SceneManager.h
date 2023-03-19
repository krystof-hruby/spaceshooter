// SceneManager.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>

#include "Scene.h"

// Manages scenes.
class SceneManager {
private:
	SceneManager() { }
	SceneManager(SceneManager const& copy) = delete;
	SceneManager operator = (SceneManager const& copy) = delete;
	
	std::shared_ptr<Scene> current_scene;

public:
	static SceneManager& GetInstance();
	
	void ChangeScene(std::shared_ptr<Scene> scene);
	std::shared_ptr<Scene> GetCurrentScene();
};

