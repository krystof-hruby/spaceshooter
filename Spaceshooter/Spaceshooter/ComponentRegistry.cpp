// ComponentRegistry.cpp
// Krystof Hruby
// 2023

#include "ComponentRegistry.h"

void ComponentRegistry::Start(std::unordered_map<UUID, std::shared_ptr<Component>> components) {
	for (auto component : components) {
		component.second->Start();
	}
}

void ComponentRegistry::Update(std::unordered_map<UUID, std::shared_ptr<Component>> components) {
	for (auto component : components) {
		component.second->Update();
	}
}

void ComponentRegistry::StartAllComponents() {
	this->Start(this->components_transform);
}

void ComponentRegistry::UpdateAllComponents() {

}
