// Scene_Level1.cpp
// Krystof Hruby
// 2023

#include "Scene_Level1.h"

#include "Logging.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene_Level2.h"

void Scene_Level1::Start() {
	LOG("LEVEL 1: Loading level 1. Scene UUID: " + std::to_string(this->GetID()));

	std::shared_ptr<GameObject> test = std::make_shared<GameObject>(this->component_registry);
	std::shared_ptr<Component_Transform> test_transform = std::make_shared<Component_Transform>(test);
	
	test->AddComponent<Component_Transform>(test_transform);

	LOG(test->GetID());
	LOG(test->GetComponent<Component_Transform>()->GetGameObject()->GetID());

	SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level2>());
}

void Scene_Level1::Update() {

}

void Scene_Level1::End() {
	LOG("LEVEL 1: Unloading level 1. Scene UUID: " + std::to_string(this->GetID()));
}