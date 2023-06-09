// CollisionManager.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_Collider.h"

// Manages collider components.
class CollisionManager final : public Identifiable {
public:
	// Checks whether any colliders collide with any other colliders. O((n^2 - n) / 2).
	void HandleCollisions() const;

	// Register collider to collide.
	void RegisterCollider(std::shared_ptr<Component_Collider> component_collider);

	// Unregister collider from colliding.
	void UnregisterCollider(std::shared_ptr<Component_Collider> component_collider);

private:
	// Array-list (vector) over linked list to maximize cache hits.
	// Unregistering - removing and element - is almost never called, while iteration is called every frame.
	std::vector<std::shared_ptr<Component_Collider>> collider_components;
};

