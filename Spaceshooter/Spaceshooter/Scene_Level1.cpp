// Scene_Level1.cpp
// Krystof Hruby
// 2023

#include "Scene_Level1.h"

#include "Component_Level1Manager.h"
#include "GameObjectFactory.h"
#include "Logging.h"
#include "Sprites.h"

void Scene_Level1::Load() {
	LOG("LEVEL 1: Loading level 1. Scene UUID: " + std::to_string(this->GetID()));

	// Fader.
	std::shared_ptr<GameObject> fader = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Fader, this->component_registry);
	Scene::Instantiate(fader);

	// Background.
	std::shared_ptr<GameObject> background = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Background, this->component_registry);
	background->GetComponent<Component_SpriteRenderer>()->SetSprite(SPRITE_BACKGROUND_BLACK);
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
	std::shared_ptr<GameObject> level1manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Level1Manager, this->component_registry);
	level1manager->GetComponent<Component_Level1Manager>()->fader_sprite_renderer = fader->GetComponent<Component_SpriteRenderer>();
	level1manager->GetComponent<Component_Level1Manager>()->scripted_event_commander_talk = scripted_events->GetComponent<Component_ScriptedEvent_CommanderTalk>();
	level1manager->GetComponent<Component_Level1Manager>()->commander_frame_transform = commander_ui->GetComponent<Component_Transform>();
	Scene::Instantiate(level1manager);
}

void Scene_Level1::Unload() {
	LOG("LEVEL 1: Unloading level 1. Scene UUID: " + std::to_string(this->GetID()));

	AudioPlayer::GetInstance().StopAllAudioClips();
}

