// Component_Level1Manager.cpp
// Krystof Hruby
// 2023

#include "Component_Level1Manager.h"

#include "Component_Animator.h"
#include "Component_PlayerController.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Scene_Level2.h"
#include "SceneManager.h"
#include "Time.h"

// This could have also been done with a state machine.
// But state machines take so much unecessary time to write and so much space.
// And this is still quite understandable and readable.
// Only a few additional bool checks per frame to performance.
void Component_Level1Manager::Update() {
	if (!this->commander_frame_spawned && this->level_time > this->spawn_commander_frame_time) {
		this->commander_frame_transform.lock()->scale += (float)Time::delta_time * 15;

		if (this->commander_frame_transform.lock()->scale >= 0.4f) {
			this->commander_frame_transform.lock()->scale = 0.4f;
			this->commander_frame_spawned = true;
		}
	}

	if (!this->intro_activated && this->level_time > this->start_intro_time) {
		this->scripted_event_commander_talk.lock()->Activate("text level 1 intro");
		this->intro_activated = true;
	}

	if (!this->player_spawned && this->level_time > this->spawn_player_time) {
		auto player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, this->GetGameObject()->GetComponentRegistry());
		Scene::Instantiate(player);
		this->player_spawned = true;
	}

	if (!this->asteroids_spawned && this->level_time > this->start_spawning_asteroids_time) {
		auto asteroids_manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::AsteroidsManager, this->GetGameObject()->GetComponentRegistry());
		Scene::Instantiate(asteroids_manager);
		this->asteroids_spawned = true;
	}

	if (!this->cutscene1_activated && this->level_time > this->cutscene1_time) {
		this->scripted_event_commander_talk.lock()->Activate("text level 1 cutscene 1");
		this->cutscene1_activated = true;
	}
	else if (!this->cutscene2_activated && this->level_time > this->cutscene2_time) {
		this->scripted_event_commander_talk.lock()->Activate("text level 1 cutscene 2");
		this->cutscene2_activated = true;
	}
	else if (!this->cutscene3_activated && this->level_time > this->cutscene3_time) {
		this->scripted_event_commander_talk.lock()->Activate("text level 1 cutscene 3");
		this->cutscene3_activated = true;
	}

	if (this->level_time > this->level_length) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level2>());
	}

	this->level_time += (float)Time::delta_time;
}

