// Scene_Level3.cpp
// Krystof Hruby
// 2023

#include "Scene_Level3.h"

#include "Component_PlayerController.h"
#include "GameObjectFactory.h"
#include "Logging.h"
#include "Sprites.h"

void Scene_Level3::Load() {
	LOG("LEVEL 3: Loading level 3. Scene UUID: " + std::to_string(this->GetID()));

	// Fader.
	std::shared_ptr<GameObject> fader = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Fader, this->component_registry);
	Scene::Instantiate(fader);

	// Background.
	std::shared_ptr<GameObject> background = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Background, this->component_registry);
	background->GetComponent<Component_SpriteRenderer>()->SetSprite(SPRITE_BACKGROUND_PURPLE);
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
	std::shared_ptr<GameObject> level3manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Level3Manager, this->component_registry);
	level3manager->GetComponent<Component_Level3Manager>()->fader_sprite_renderer = fader->GetComponent<Component_SpriteRenderer>();
	level3manager->GetComponent<Component_Level3Manager>()->scripted_event_commander_talk = scripted_events->GetComponent<Component_ScriptedEvent_CommanderTalk>();
	level3manager->GetComponent<Component_Level3Manager>()->commander_frame_transform = commander_ui->GetComponent<Component_Transform>();
	Scene::Instantiate(level3manager);
}

void Scene_Level3::Unload() {
	LOG("LEVEL 3: Unloading level 3. Scene UUID: " + std::to_string(this->GetID()));

	AudioPlayer::GetInstance().StopAllAudioClips();
}
