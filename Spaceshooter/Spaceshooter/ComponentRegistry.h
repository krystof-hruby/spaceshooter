// ComponentRegistry.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>
#include <unordered_map>

#include "Identifiable.h"
// Components:
#include "Component_Transform.h"
#include "Component_SpriteRenderer.h"
#include "Component_InputReader.h"
#include "Component_SoundEmitter.h"

// Holds data of all components in a scene.
class ComponentRegistry : public Identifiable {
private:
	std::unordered_map<ObjectUUID, std::shared_ptr<Component_Transform>> components_transform;
	std::unordered_map<ObjectUUID, std::shared_ptr<Component_SpriteRenderer>> components_sprite_renderer;
	std::unordered_map<ObjectUUID, std::shared_ptr<Component_InputReader>> components_input_reader;
	std::unordered_map<ObjectUUID, std::shared_ptr<Component_SoundEmitter>> components_sound_emitter;

	template<typename ComponentType>
	void Components_Start(std::unordered_map<ObjectUUID, std::shared_ptr<ComponentType>> components) {
		for (auto component : components) {
			component.second->Start();
		}
	}
	
	template<typename ComponentType>
	void Components_Update(std::unordered_map<ObjectUUID, std::shared_ptr<ComponentType>> components) {
		for (auto component : components) {
			component.second->Update();
		}
	}

public:
	// Calls start on all currently registered components.
	void AllComponents_Start();
	// Calls update on all currently registered components.
	void AllComponents_Update();
	
	// COMPONENTS:

	template<typename ComponentType>
	std::shared_ptr<ComponentType> GetComponent(ObjectUUID game_object_id);
	template<typename ComponentType>
	void AddComponent(ObjectUUID game_object_id, std::shared_ptr<ComponentType> component);
	template<typename ComponentType>
	void RemoveComponent(ObjectUUID game_object_id);

	// Component_Transform:
	template<>
	std::shared_ptr<Component_Transform> GetComponent<Component_Transform>(ObjectUUID game_object_id) {
		return this->components_transform[game_object_id];
	}
	template<>
	void AddComponent<Component_Transform>(ObjectUUID game_object_id, std::shared_ptr<Component_Transform> component) {
		this->components_transform.insert({ game_object_id, component });
	}
	template<>
	void RemoveComponent<Component_Transform>(ObjectUUID game_object_id) {
		this->components_transform.erase(game_object_id);
	}

	// Component_SpriteRenderer:
	template<>
	std::shared_ptr<Component_SpriteRenderer> GetComponent<Component_SpriteRenderer>(ObjectUUID game_object_id) {
		return this->components_sprite_renderer[game_object_id];
	}
	template<>
	void AddComponent<Component_SpriteRenderer>(ObjectUUID game_object_id, std::shared_ptr<Component_SpriteRenderer> component) {
		this->components_sprite_renderer.insert({ game_object_id, component });
	}
	template<>
	void RemoveComponent<Component_SpriteRenderer>(ObjectUUID game_object_id) {
		this->components_sprite_renderer.erase(game_object_id);
	}

	// Component_InputReader:
	template<>
	std::shared_ptr<Component_InputReader> GetComponent<Component_InputReader>(ObjectUUID game_object_id) {
		return this->components_input_reader[game_object_id];
	}
	template<>
	void AddComponent<Component_InputReader>(ObjectUUID game_object_id, std::shared_ptr<Component_InputReader> component) {
		this->components_input_reader.insert({ game_object_id, component });
	}
	template<>
	void RemoveComponent<Component_InputReader>(ObjectUUID game_object_id) {
		this->components_input_reader.erase(game_object_id);
	}

	// Component_SoundEmitter:
	template<>
	std::shared_ptr<Component_SoundEmitter> GetComponent<Component_SoundEmitter>(ObjectUUID game_object_id) {
		return this->components_sound_emitter[game_object_id];
	}
	template<>
	void AddComponent<Component_SoundEmitter>(ObjectUUID game_object_id, std::shared_ptr<Component_SoundEmitter> component) {
		this->components_sound_emitter.insert({ game_object_id, component });
	}
	template<>
	void RemoveComponent<Component_SoundEmitter>(ObjectUUID game_object_id) {
		this->components_sound_emitter.erase(game_object_id);
	}
};

