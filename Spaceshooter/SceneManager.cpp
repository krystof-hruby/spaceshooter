// SceneManager.cpp
// Krystof Hruby
// 2023

#include "SceneManager.h"

SceneManager& SceneManager::GetInstance() {
	static SceneManager instance;
	return instance;
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> scene) {
	if (this->current_scene)
		this->current_scene->Unload();
	
	this->current_scene = scene;
	this->current_scene->Load();
}

std::shared_ptr<Scene> SceneManager::GetCurrentScene() {
	return this->current_scene;
}