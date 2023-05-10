// Component_Level1Manager.cpp
// Krystof Hruby
// 2023

#include "Component_Level1Manager.h"

#include "AudioClips.h"
#include "Component_PlayerController.h"
#include "GameObjectFactory.h"
#include "Scene_Level1.h"
#include "Scene_Level2.h"
#include "SceneManager.h"
#include "Time.h"

// This could have also been done with a state machine.
// But state machines take so much unecessary time to write and so much space.
// And this is still quite understandable and readable.
void Component_Level1Manager::Update() {
	// If level failed despawn commander frame and fade out.
	if (this->level_failed) {
		this->level_failed_time += (float)Time::delta_time;

		// Despawn commander frame.
		if (!this->level_failed_commander_frame_despawned && this->level_failed_time > this->level_failed_despawn_commander_frame_time) {
			AudioPlayer::GetInstance().PlayAudioClip(AUDIO_BLEEP, 85);
			this->commander_frame_transform.lock()->scale -= (float)Time::delta_time * 15;

			if (this->commander_frame_transform.lock()->scale <= 0) {
				this->commander_frame_transform.lock()->scale = 0;
				this->level_failed_commander_frame_despawned = true;
			}
		}

		// Fade out.
		if (!this->faded_out && this->level_failed_time > this->level_failed_fade_out_time) {
			this->fader_sprite_renderer.lock()->transparency -= (float)Time::delta_time;

			if (this->fader_sprite_renderer.lock()->transparency <= 0) {
				this->fader_sprite_renderer.lock()->transparency = 0;
				this->faded_out = true;
			}
		}

		// Restart from level 1.
		if (this->level_failed_time > this->level_failed_length) {
			SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level1>());
		}

		return;
	}

	// Fade in.
	if (!this->faded_in && this->level_time && this->fade_in_time) {
		this->fader_sprite_renderer.lock()->transparency += (float)Time::delta_time;

		if (this->fader_sprite_renderer.lock()->transparency >= 1) {
			this->fader_sprite_renderer.lock()->transparency = 1;
			this->faded_in = true;
		}
	}
	
	// Spawn commander frame.
	if (!this->commander_frame_spawned && this->level_time > this->spawn_commander_frame_time) {
		AudioPlayer::GetInstance().PlayAudioClip(AUDIO_BLEEP, 85);
		this->commander_frame_transform.lock()->scale += (float)Time::delta_time * 15;

		if (this->commander_frame_transform.lock()->scale >= 0.4f) {
			this->commander_frame_transform.lock()->scale = 0.4f;
			this->commander_frame_spawned = true;
		}
	}

	// Start intro + tutorial.
	if (!this->intro_activated && this->level_time > this->intro_time) {
		this->scripted_event_commander_talk.lock()->Activate("text level 1 intro");
		this->intro_activated = true;
	}

	// Spawn player.
	if (!this->player_spawned && this->level_time > this->spawn_player_time) {
		auto player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, this->GetGameObject()->GetComponentRegistry());
		player->GetComponent<Component_PlayerController>()->level1manager = this->shared_from_this();
		Scene::Instantiate(player);
	
		this->player_controller = player->GetComponent<Component_PlayerController>();
		this->player_spawned = true;
	}

	// Spawn asteroids manager.
	if (!this->asteroids_spawned && this->level_time > this->start_spawning_asteroids_time) {
		auto asteroids_manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::AsteroidsManager, this->GetGameObject()->GetComponentRegistry());
		Scene::Instantiate(asteroids_manager);
		
		this->asteroids_spawned = true;
	}

	// Play cutscenes and outro.
	if (!this->cutscene1_activated && this->level_time > this->cutscene1_time) {
		this->scripted_event_commander_talk.lock()->Activate("text level 1 cutscene 1");
		this->cutscene1_activated = true;
	} else if (!this->cutscene2_activated && this->level_time > this->cutscene2_time) {
		this->scripted_event_commander_talk.lock()->Activate("text level 1 cutscene 2");
		this->cutscene2_activated = true;
	} else if (!this->cutscene3_activated && this->level_time > this->cutscene3_time) {
		this->scripted_event_commander_talk.lock()->Activate("text level 1 cutscene 3");
		this->cutscene3_activated = true;
	} else if (!this->outro_activated && this->level_time > this->outro_time) {
		this->scripted_event_commander_talk.lock()->Activate("text level 1 outro");
		this->outro_activated = true;
	}

	// Despawn player.
	if (!this->despawned_player && this->level_time > this->despawn_player_time) {
		this->player_controller.lock()->Despawn();
		this->despawned_player = true;
	}

	// Despawn commander frame.
	if (!this->commander_frame_despawned && this->level_time > this->despawn_commander_frame_time) {
		AudioPlayer::GetInstance().PlayAudioClip(AUDIO_BLEEP, 85);
		this->commander_frame_transform.lock()->scale -= (float)Time::delta_time * 15;

		if (this->commander_frame_transform.lock()->scale <= 0) {
			this->commander_frame_transform.lock()->scale = 0;
			this->commander_frame_despawned = true;
		}
	}

	// Fade out.
	if (!this->faded_out && this->level_time > this->fade_out_time) {
		this->fader_sprite_renderer.lock()->transparency -= (float)Time::delta_time;

		if (this->fader_sprite_renderer.lock()->transparency <= 0) {
			this->fader_sprite_renderer.lock()->transparency = 0;
			this->faded_out = true;
		}
	}

	// End level.
	if (this->level_time > this->level_length) {
		SceneManager::GetInstance().ChangeScene(std::make_shared<Scene_Level2>());
	}

	this->level_time += (float)Time::delta_time;
}

void Component_Level1Manager::LevelFailed() {
	bool activated = this->scripted_event_commander_talk.lock()->Activated();
	this->scripted_event_commander_talk.lock()->Deactivate();
	this->scripted_event_commander_talk.lock()->Activate("text fail", activated);
	this->level_failed = true;
}

