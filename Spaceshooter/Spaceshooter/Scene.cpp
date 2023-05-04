// Scene.cpp
// Krystof Hruby
// 2023

#include "Scene.h"

#include "Logging.h"
#include "mysoundengine.h"
#include "SceneManager.h"

void Scene::Update() const {
	this->component_registry->AllComponents_Update();
}

void Scene::Instantiate(std::shared_ptr<GameObject> game_object) {
	SceneManager::GetInstance().GetCurrentScene()->scene_objects.push_back(game_object);
}