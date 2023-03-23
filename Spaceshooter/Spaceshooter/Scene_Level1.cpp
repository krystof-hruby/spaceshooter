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

std::shared_ptr<GameObject> test;
std::shared_ptr<GameObject> test1;

void f(std::shared_ptr<GameObject> other) {
	LOG("Hello");
}

void g(std::shared_ptr<GameObject> other) {
	LOG("Hi");
}

void Scene_Level1::Load() {
	LOG("LEVEL 1: Loading level 1. Scene UUID: " + std::to_string(this->GetID()));

	test = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Test, this->component_registry);
	test1 = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Test, this->component_registry);

	test->GetComponent<Component_RectangleCollider>()->SetOnCollisionEnter(f);
	test->GetComponent<Component_RectangleCollider>()->SetOnCollisionLeave(g);
	test1->GetComponent<Component_RectangleCollider>()->SetOnCollisionEnter(g);

	this->component_registry->AllComponents_Start();
}

void Scene_Level1::Update() {
	this->component_registry->AllComponents_Update();

	test->GetComponent<Component_Transform>()->position.YValue++;
}

void Scene_Level1::Unload() {
	LOG("LEVEL 1: Unloading level 1. Scene UUID: " + std::to_string(this->GetID()));
	this->StopAllSounds();
}
