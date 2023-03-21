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