// Gameloop.cpp
// Krystof Hruby
// 2023

#include "Gameloop.h"

#include <memory>

#include "InputManager.h"
#include "Logging.h"
#include "SceneManager.h"
#include "Scene_Level1.h"

void Gameloop::Start() {
	LOG("GAMELOOP: Starting the game.");

	// Load level 1
	SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level1>());
}

void Gameloop::Update(double frame_time) {
	Time::delta_time = frame_time;
	
	InputManager::GetInstance().Update();

	SceneManager::GetInstance().GetCurrentScene()->Update();
	SceneManager::GetInstance().GetCurrentScene()->Components_Update();
	SceneManager::GetInstance().GetCurrentScene()->UpdateComponentRegistry();
}

void Gameloop::End() {
	LOG("GAMELOOP: Ending the game.");

	SceneManager::GetInstance().GetCurrentScene()->Unload();
}
