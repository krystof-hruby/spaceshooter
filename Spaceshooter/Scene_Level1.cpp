// Scene_Level1.cpp
// Krystof Hruby
// 2023

#include "Scene_Level1.h"
#include "Logging.h"

void Scene_Level1::Start() {
	LOG(("Loading level 1. Scene ID: " + this->GetID().AsString()));
}

void Scene_Level1::Update() {
}

void Scene_Level1::End() {
	LOG("Unloading level 1. Scene ID: " + this->GetID().AsString());
}