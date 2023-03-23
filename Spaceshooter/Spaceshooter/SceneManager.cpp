// SceneManager.cpp
// Krystof Hruby
// 2023

#include "SceneManager.h"

#include <string>

#include "Logging.h"

SceneManager& SceneManager::GetInstance() {
	static SceneManager instance;
	return instance;
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> scene) {
	LOG("SCENE MANAGER: Changing scene to (UUID): " + std::to_string(scene->GetID()));

	if (this->current_scene)
		this->current_scene->Unload();
	
	this->current_scene = scene;
	this->current_scene->Load();
	this->current_scene->Components_Start();
}

std::shared_ptr<Scene> SceneManager::GetCurrentScene() {
	return this->current_scene;
}