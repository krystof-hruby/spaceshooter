// CollisionManager.cpp
// Krystof Hruby
// 2023

#include "CollisionManager.h"

void CollisionManager::HandleCollisions() const {
	// Iterate throught all of the colliders and check whether they collide with any other collider.
	for (auto i = this->collider_components.begin(); i < this->collider_components.end(); i++)
		for (auto j = (i + 1); j < this->collider_components.end(); j++)
			(*i)->HandleCollision(*j);
}

void CollisionManager::RegisterCollider(std::shared_ptr<Component_Collider> component_collider) {
	this->collider_components.push_back(component_collider);
}

void CollisionManager::UnregisterCollider(std::shared_ptr<Component_Collider> component_collider) {
	// Must loop through all elements to locate the collider.
	for (int i = 0; i < this->collider_components.size(); i++)
		if (this->collider_components[i] == component_collider)
			this->collider_components.erase(this->collider_components.begin() + i);
}
