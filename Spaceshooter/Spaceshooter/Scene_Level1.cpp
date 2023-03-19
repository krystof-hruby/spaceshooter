// Scene_Level1.cpp
// Krystof Hruby
// 2023

#include "Scene_Level1.h"

#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Logging.h"
#include "SceneManager.h"
#include "Scene_Level2.h"

void Scene_Level1::Start() {
	LOG("LEVEL 1: Loading level 1. Scene UUID: " + std::to_string(this->GetID()));

	std::shared_ptr<GameObject> test = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Blank, this->component_registry);

	LOG(test->GetID());

	//SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level2>());
}

void Scene_Level1::Update() {

}

void Scene_Level1::End() {
	LOG("LEVEL 1: Unloading level 1. Scene UUID: " + std::to_string(this->GetID()));
}