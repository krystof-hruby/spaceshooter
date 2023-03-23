// Scene.cpp
// Krystof Hruby
// 2023

#include "Scene.h"

#include "Logging.h"
#include "mysoundengine.h"

Scene::Scene() { }

void Scene::StopAllSounds() {
	LOG("SCENE: Stopping all sounds.");
	MySoundEngine::GetInstance()->StopAllSounds();
}

void Scene::Components_Start() {
	this->component_registry->AllComponents_Start();
}

void Scene::Components_Update() {
	this->component_registry->AllComponents_Update();
}

void Scene::Load() { }

void Scene::Update() { }

void Scene::Unload() { }
