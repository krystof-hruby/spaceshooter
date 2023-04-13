// Component_Collider.h
// Krystof Hruby
// 2023

#pragma once

#include <functional>

#include "Component.h"
#include "Global.h"
#include "Shapes.h"
#include "vector2D.h"

// Enables collision with other collidable objects.
class Component_Collider : public Component {
private:
	bool in_collision = false;

	// Checks whether the collider collides with other.
	bool CollidesWith(std::shared_ptr<Component_Collider> other);

	// Activates first frame of collision.
	std::function<void(std::shared_ptr<GameObject>)> OnCollisionEnter;

	// Activates every frame of collision.
	std::function<void(std::shared_ptr<GameObject>)> OnCollisionStay;
	
	// Activates one frame after collision.
	std::function<void(std::shared_ptr<GameObject>)> OnCollisionLeave;
protected:
	// Returns shape of the collider. Override for each different collider type.
	virtual std::shared_ptr<IShape2D> GetShape() = 0;

	// Returns the world coordinates of this collider.
	Vector2D GetWorldPosition();

	// Updates position of Shape with PlaceAt functions from the Shell.
	// Override for each collider shape.
	virtual void UpdatePosition() = 0;

public:
	using Component::Component;

	// Override and set to true if this component starts. Currently: saves performance by ignoring Start function of this component type.
	inline virtual bool Startable() const override { return false; }

	// Do not override in derived classes.
	inline bool Updatable() const override final { return true; }

	// Relative position to game object's transform.
	Vector2D position_offset;

	// Provide OnCollisionEnter function if required.
	// Activates first frame of collision.
	void SetOnCollisionEnter(std::function<void(std::shared_ptr<GameObject>)> on_collision_enter);

	// Provide OnCollisionStay function if required.
	// Activates every frame of collision.
	void SetOnCollisionStay(std::function<void(std::shared_ptr<GameObject>)> on_collision_stay);
	
	// Provide OnCollisionLeave function if required.
	// Activates one frame after collision.
	void SetOnCollisionLeave(std::function<void(std::shared_ptr<GameObject>)> on_collision_leave);

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

