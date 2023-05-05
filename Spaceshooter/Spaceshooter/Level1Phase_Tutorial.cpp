// Leve1Phase_Tutorial.cpp
// Krystof Hruby
// 2023

#include "Level1Phase_Tutorial.h"

#include "Component_Animator.h"
#include "Component_Level1Manager.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Scene.h"
#include "Time.h"

void Level1Phase_Tutorial::Play(std::shared_ptr<Component_Level1Manager> level1manager) {
	if (!this->commander_spawned && level1manager->commander_ui.lock()->GetComponent<Component_Animator>()->AnimationFinished("commander spawn")) {
		level1manager->commander_ui.lock()->GetComponent<Component_Animator>()->PlayAnimation("commander talk");
		level1manager->text_ui.lock()->GetComponent<Component_Animator>()->PlayAnimation("text intro");
		this->commander_spawned = true;
	}

	if (this->commander_spawned) {
		if (!this->warped_player_in && level1manager->text_ui.lock()->GetComponent<Component_Animator>()->AnimationFinished("text intro")) {
			std::shared_ptr<GameObject> player = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::Player, level1manager->component_registry.lock());
			Scene::Instantiate(player);
	
			level1manager->text_ui.lock()->GetComponent<Component_Animator>()->PlayAnimation("text tutorial");
			this->warped_player_in = true;
		}

		if (level1manager->text_ui.lock()->GetComponent<Component_Animator>()->AnimationFinished("text tutorial")) {
			level1manager->commander_ui.lock()->GetComponent<Component_Animator>()->PlayAnimation("commander spawn");
			level1manager->ChangePhase(level1manager->phase_gameplay);
		}
	}
}
