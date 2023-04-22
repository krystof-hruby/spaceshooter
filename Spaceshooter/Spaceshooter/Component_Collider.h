// Component_Collider.h
// Krystof Hruby
// 2023

#pragma once

#include <unordered_set>

#include "Component.h"
#include "Global.h"
#include "Shapes.h"
#include "vector2D.h"

// Enables collision with other collidable objects.
class Component_Collider : public Component {
private:
	std::unordered_set<ObjectUUID> in_collision_with;
	bool IsInCollisionWith(ObjectUUID other_id);

	// Checks whether the collider collides with other.
	bool CollidesWith(std::shared_ptr<Component_Collider> other);

protected:
	// Returns shape of the collider. Override for each different collider type.
	virtual std::shared_ptr<IShape2D> GetShape() = 0;

	// Returns the world coordinates of this collider.
	Vector2D GetWorldPosition();

	// Updates position of Shape with PlaceAt functions from the Shell.
	// Override for each collider shape.
	virtual void UpdatePosition() = 0;

	// Activates first frame of collision.
	virtual void OnCollisionEnter(std::shared_ptr<GameObject> other);

	// Activates every frame of collision.
	virtual void OnCollisionStay(std::shared_ptr<GameObject> other);
	
	// Activates one frame after collision.
	virtual void OnCollisionLeave(std::shared_ptr<GameObject> other);

public:
	using Component::Component;

	// Override and set to true if this component starts. Currently: saves performance by ignoring Start function of this component type.
	inline virtual bool Startable() const override { return false; }

	// Do not override in derived classes.
	inline bool Updatable() const override final { return true; }

	// Relative position to game object's transform.
	Vector2D position_offset;

	// Handles collision. Does nothing if not colliding with other (besides OnCollisionLeave which activates one frame after collision).
	// Called every frame by component registry, alongside Update.
	void HandleCollision(std::shared_ptr<Component_Collider> other);

	// Updates position of the collider. Do not override in subclasses.
	void Update() override final;

#if VISUALIZE_HITBOXES
	// Displays the hitbox of this collider. Override for each collider type.
	virtual void VisualizeHitbox() = 0;
#endif
};

