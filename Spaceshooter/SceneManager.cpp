// SceneManager.cpp
// Krystof Hruby
// 2023

#include "SceneManager.h"
#include "Logging.h"

SceneManager& SceneManager::GetInstance() {
	static SceneManager instance;
	return instance;
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> scene) {
	LOG(("Changing scene to (ID): " + scene->GetID().AsString()) + ".");

	if (this->current_scene)
		this->current_scene->End();
	
	this->current_scene = scene;
	this->current_scene->Start();
}

std::shared_ptr<Scene> SceneManager::GetCurrentScene() {
	return this->current_scene;
}