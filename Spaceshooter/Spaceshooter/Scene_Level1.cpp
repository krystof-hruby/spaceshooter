// Scene_Level1.cpp
// Krystof Hruby
// 2023

#include "Scene_Level1.h"

#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Logging.h"
#include "SceneManager.h"
#include "Scene_Level2.h"
#include "Component_RectangleCollider.h"
#include "Component_Transform.h"

void Scene_Level1::Load() {
	LOG("LEVEL 1: Loading level 1. Scene UUID: " + std::to_string(this->GetID()));

	player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, this->component_registry);

}

void Scene_Level1::Update() {

}

void Scene_Level1::Unload() {
	LOG("LEVEL 1: Unloading level 1. Scene UUID: " + std::to_string(this->GetID()));

	this->StopAllSounds();
}
