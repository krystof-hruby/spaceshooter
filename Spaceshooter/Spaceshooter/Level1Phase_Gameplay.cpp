// Level1Phase_Gameplay.cpp
// Krystof Hruby
// 2023

#include "Level1Phase_Gameplay.h"

#include "Component_Animator.h"
#include "Component_AsteroidsManager.h"
#include "Component_Level1Manager.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Scene.h"
#include "Time.h"

void Level1Phase_Gameplay::Play(std::shared_ptr<Component_Level1Manager> level1manager) {
	if (!this->played_start && level1manager->commander_ui.lock()->GetComponent<Component_Animator>()->AnimationFinished("commander spawn")) {
		level1manager->commander_ui.lock()->GetComponent<Component_Animator>()->PlayAnimation("commander talk");
		level1manager->text_ui.lock()->GetComponent<Component_Animator>()->PlayAnimation("text level 1 start");
		this->played_start = true;
	}

	if (!this->spawned_asteroids_manager && this->played_start && level1manager->text_ui.lock()->GetComponent<Component_Animator>()->AnimationFinished("text level 1 start")) {
		std::shared_ptr<GameObject> asteroids_manager = GameObjectFactory::GetInstance().CreateGameObject(GameObjectType::AsteroidsManager, level1manager->component_registry.lock());
		asteroids_manager->GetComponent<Component_AsteroidsManager>()->score_manager = level1manager->GetGameObject()->GetComponent<Component_Level1Manager>()->score_manager;
		Scene::Instantiate(asteroids_manager);
		
		this->spawned_asteroids_manager = true;

		level1manager->text_ui.lock()->GetComponent<Component_Animator>()->PlayAnimation("text storm incoming");
	}
}
