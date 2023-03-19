// Scene_Level2.cpp
// Krystof Hruby
// 2023

#include "Scene_Level2.h"

#include "Logging.h"

void Scene_Level2::Load() {
	LOG("LEVEL 2: Loading level 2. Scene UUID: " + std::to_string(this->GetID()));

}

void Scene_Level2::Update() {

}

void Scene_Level2::Unload() {
	LOG("LEVEL 2: Unloading level 2. Scene UUID: " + std::to_string(this->GetID()));

}