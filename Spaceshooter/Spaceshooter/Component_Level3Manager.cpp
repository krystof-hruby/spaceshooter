// Component_Level3Manager.cpp
// Krystof Hruby
// 2023

#include "Component_Level3Manager.h"

#include "AudioClips.h"
#include "Component_BossController.h"
#include "Component_PlayerController.h"
#include "gamecode.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Scene_Level1.h"
#include "SceneManager.h"
#include "Time.h"

void Component_Level3Manager::Update() {
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

	if (this->level_finished) {
		this->level_finished_time += (float)Time::delta_time;

		// Despawn player.
		if (!this->despawned_player && this->level_finished_time > this->level_finished_despawn_player_time) {
			this->player_controller.lock()->Despawn();
			this->despawned_player = true;
		}

		// Despawn commander frame.
		if (!this->commander_frame_despawned && this->level_finished_time > this->level_finished_despawn_commander_frame_time) {
			AudioPlayer::GetInstance().PlayAudioClip(AUDIO_BLEEP, 85);
			this->commander_frame_transform.lock()->scale -= (float)Time::delta_time * 15;

			if (this->commander_frame_transform.lock()->scale <= 0) {
				this->commander_frame_transform.lock()->scale = 0;
				this->commander_frame_despawned = true;
			}
		}

		// Fade out.
		if (!this->faded_out && this->level_finished_time > this->level_failed_fade_out_time) {
			this->fader_sprite_renderer.lock()->transparency -= (float)Time::delta_time;

			if (this->fader_sprite_renderer.lock()->transparency <= 0) {
				this->fader_sprite_renderer.lock()->transparency = 0;
				this->faded_out = true;
			}
		}

		// End game.
		if (this->level_finished_time > this->level_finished_length) {
			Game::instance.ChangeState(Game::GameState::MENU);
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

	// Play intro.
	if (!this->intro_activated && this->level_time > this->intro_time) {
		this->scripted_event_commander_talk.lock()->Activate("text level 3 intro");
		this->intro_activated = true;
	}

	// Spawn player.
	if (!this->player_spawned && this->level_time > this->spawn_player_time) {
		auto player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, this->GetGameObject()->GetComponentRegistry());
		player->GetComponent<Component_PlayerController>()->level3manager = this->shared_from_this();
		Scene::Instantiate(player);

		this->player_controller = player->GetComponent<Component_PlayerController>();
		this->player_spawned = true;
	}

	// Spawn boss.
	if (!this->boss_spawned && this->level_time > this->spawn_boss_time) {
		auto boss = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Boss, this->GetGameObject()->GetComponentRegistry());
		boss->GetComponent<Component_BossController>()->player_transform = this->player_controller.lock()->GetGameObject()->GetComponent<Component_Transform>();
		Scene::Instantiate(boss);

		this->boss_controller = boss->GetComponent<Component_BossController>();
		this->boss_spawned = true;
	}

	// Play cutscenes and outro.
	if (!this->boss_controller.expired()) {
		if (!this->cutscene1_activated && this->boss_controller.lock()->health <= 150) {
			this->scripted_event_commander_talk.lock()->Activate("text level 3 cutscene 1");
			this->cutscene1_activated = true;
		} else if (!this->cutscene2_activated && this->boss_controller.lock()->health <= 100) {
			this->scripted_event_commander_talk.lock()->Activate("text level 3 cutscene 2");
			this->cutscene2_activated = true;
		} else if (!this->cutscene3_activated && this->boss_controller.lock()->health <= 50) {
			this->scripted_event_commander_talk.lock()->Activate("text level 3 cutscene 3");
			this->cutscene3_activated = true;
		} else if (!this->outro_activated && this->boss_controller.lock()->health <= 0) {
			this->LevelFinished();
			this->outro_activated = true;
		}
	}

	this->level_time += (float)Time::delta_time;
}

void Component_Level3Manager::LevelFailed() {
	bool activated = this->scripted_event_commander_talk.lock()->Activated();
	this->scripted_event_commander_talk.lock()->Deactivate();
	this->scripted_event_commander_talk.lock()->Activate("text fail", activated);
	this->level_failed = true;
}

void Component_Level3Manager::LevelFinished() {
	bool activated = this->scripted_event_commander_talk.lock()->Activated();
	this->scripted_event_commander_talk.lock()->Deactivate();
	this->scripted_event_commander_talk.lock()->Activate("text level 3 outro", activated);
	this->level_finished = true;
}
