// Gameloop.cpp
// Krystof Hruby
// 2023

#include "Gameloop.h"

#include "ImageRenderer.h"
#include "InputManager.h"
#include "Logging.h"
#include "SceneManager.h"
#include "Scene_Level1.h"
#include "Scene_Level2.h"
#include "Scene_Level3.h"
#include "Time.h"

void Gameloop::Start() {
	LOG("GAMELOOP: Starting the game.");

	// Set rng seed.
	srand((unsigned int)time(NULL));

	#ifndef START_LEVEL
		SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level1>());
	#elif START_LEVEL == 1
		SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level1>());
	#elif START_LEVEL == 2
		SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level2>());
	#elif START_LEVEL == 3
		SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level3>());
	#endif
}

void Gameloop::Update(double frame_time) {
	Time::delta_time = frame_time;
	
	InputManager::GetInstance().Update();

	SceneManager::GetInstance().GetCurrentScene()->Update();

	ImageRenderer::GetInstance().RenderScheduledImages();
}

void Gameloop::End() {
	LOG("GAMELOOP: Ending the game.");

	SceneManager::GetInstance().GetCurrentScene()->Unload();
}
