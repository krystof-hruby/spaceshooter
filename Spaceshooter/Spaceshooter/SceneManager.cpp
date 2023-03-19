// SceneManager.cpp
// Krystof Hruby
// 2023

#include "SceneManager.h"

#include <string>

#include "Logging.h"

// Returns singleton instance.
SceneManager& SceneManager::GetInstance() {
	static SceneManager instance;
	return instance;
}

// Ends current scene. Starts new scene and marks it as current to be updated.
void SceneManager::ChangeScene(std::shared_ptr<Scene> scene) {
	LOG("SCENE MANAGER: Changing scene to (UUID): " + std::to_string(scene->GetID()));

	if (this->current_scene)
		this->current_scene->End();
	
	this->current_scene = scene;
	this->current_scene->Start();
}

// Returns the currently played scene.
std::shared_ptr<Scene> SceneManager::GetCurrentScene() {
	return this->current_scene;
}