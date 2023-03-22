// Component_Collider.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>

#include "Component.h"
#include "Shapes.h"

class Component_Collider : public Component {
private:
	bool in_collision = false;

	// Checks whether the collider collides with other.
	bool CollidesWith(std::shared_ptr<Component_Collider> other);

protected:
	// Returns shape of the collider. Override for each different collider type.
	virtual std::shared_ptr<IShape2D> Shape() = 0;

	// Activates first frame of collision.
	virtual void OnCollisionEnter(std::shared_ptr<GameObject> other);

	// Activates every frame of collision.
	virtual void OnCollisionStay(std::shared_ptr<GameObject> other);

	// Activates one frame after collision.
	virtual void OnCollisionLeave(std::shared_ptr<GameObject> other);

public:
	using Component::Component;

	// Handles collision. Does nothing if not colliding with other (besides OnCollisionLeave which activates one frame after collision).
	// TODO: Called every frame.
	void HandleCollision(std::shared_ptr<Component_Collider> other);
};

