// Gameloop.cpp
// Krystof Hruby
// 2023

#include "Gameloop.h"

#include <memory>

#include "Global.h"
#include "Logging.h"
#include "SceneManager.h"
#include "Scene_Level1.h"

double Time::delta_time; // Global value


// Called on START button press
void Gameloop::Start() {
	LOG("GAMELOOP: Starting the game.");

	// Load level 1
	SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level1>());
}

// Called every frame
// frame_time comes from gamecode.cpp from the Shell
void Gameloop::Update(double frame_time) {
	Time::delta_time = frame_time;
	
	SceneManager::GetInstance().GetCurrentScene()->Update();
}

// Called on MAIN MENU button press
void Gameloop::End() {
	LOG("GAMELOOP: Ending the game.");

	SceneManager::GetInstance().GetCurrentScene()->End();
}
