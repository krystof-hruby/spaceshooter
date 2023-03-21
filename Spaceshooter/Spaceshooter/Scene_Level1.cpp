// Scene_Level1.cpp
// Krystof Hruby
// 2023

#include "Scene_Level1.h"

#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Logging.h"
#include "SceneManager.h"
#include "Scene_Level2.h"

std::shared_ptr<GameObject> test;

void Scene_Level1::Load() {
	LOG("LEVEL 1: Loading level 1. Scene UUID: " + std::to_string(this->GetID()));

	test = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Test, this->component_registry);
	this->component_registry->AllComponents_Start();
}

void Scene_Level1::Update() {
	this->component_registry->AllComponents_Update();
}

void Scene_Level1::Unload() {
	LOG("LEVEL 1: Unloading level 1. Scene UUID: " + std::to_string(this->GetID()));
	this->StopAllSounds();
}