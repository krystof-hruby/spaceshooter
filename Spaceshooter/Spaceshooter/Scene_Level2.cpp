// Scene_Level2.cpp
// Krystof Hruby
// 2023

#include "Scene_Level2.h"

#include "AudioClips.h"
#include "Component_AsteroidsManager.h"
#include "Component_EnemyShipsManager.h"
#include "Component_Level2Manager.h"
#include "Component_PlayerController.h"
#include "GameObjectFactory.h"
#include "Logging.h"
#include "Sprites.h"

void Scene_Level2::Load() {
	LOG("LEVEL 2: Loading level 2. Scene UUID: " + std::to_string(this->GetID()));

	// Fader.
	std::shared_ptr<GameObject> fader = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Fader, this->component_registry);
	Scene::Instantiate(fader);

	// Background.
	std::shared_ptr<GameObject> background = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Background, this->component_registry);
	background->GetComponent<Component_SpriteRenderer>()->SetSprite(SPRITE_BACKGROUND_BROWN);
	Scene::Instantiate(background);

	// Text UI.
	std::shared_ptr<GameObject> text_ui = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::UI_Text, this->component_registry);
	Scene::Instantiate(text_ui);

	// Commander UI.
	std::shared_ptr<GameObject> commander_ui = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::UI_Commander, this->component_registry);
	Scene::Instantiate(commander_ui);

	// Scripted Events.
	std::shared_ptr<GameObject> scripted_events = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::ScriptedEvents, this->component_registry);
	scripted_events->GetComponent<Component_ScriptedEvent_CommanderTalk>()->commander_ui_animator = commander_ui->GetComponent<Component_Animator>();
	scripted_events->GetComponent<Component_ScriptedEvent_CommanderTalk>()->text_ui_animator = text_ui->GetComponent<Component_Animator>();
	Scene::Instantiate(scripted_events);

	// Level manager.
	std::shared_ptr<GameObject> level2manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Level2Manager, this->component_registry);
	level2manager->GetComponent<Component_Level2Manager>()->fader_sprite_renderer = fader->GetComponent<Component_SpriteRenderer>();
	level2manager->GetComponent<Component_Level2Manager>()->scripted_event_commander_talk = scripted_events->GetComponent<Component_ScriptedEvent_CommanderTalk>();
	level2manager->GetComponent<Component_Level2Manager>()->commander_frame_transform = commander_ui->GetComponent<Component_Transform>();
	Scene::Instantiate(level2manager);
}

void Scene_Level2::Unload() {
	LOG("LEVEL 2: Unloading level 2. Scene UUID: " + std::to_string(this->GetID()));

	AudioPlayer::GetInstance().StopAllAudioClips();
}
