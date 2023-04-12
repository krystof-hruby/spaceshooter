// Scene.cpp
// Krystof Hruby
// 2023

#include "Scene.h"

#include "Logging.h"
#include "mysoundengine.h"

Scene::Scene() { }

void Scene::StopAllSounds() const {
	LOG("SCENE: Stopping all sounds.");
	MySoundEngine::GetInstance()->StopAllSounds();
}

void Scene::Components_Start() const {
	this->component_registry->AllComponents_Start();
}

void Scene::Components_Update() const {
	this->component_registry->AllComponents_Update();
}

void Scene::ClearComponentRegistry() const {
	this->component_registry->ClearRegistry();
}

void Scene::Load() { }

void Scene::Update() { }

void Scene::Unload() { }
