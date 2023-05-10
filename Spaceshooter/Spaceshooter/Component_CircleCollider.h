// Component_CircleCollider.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_Collider.h"

// Collider with a circular shape.
class Component_CircleCollider : public Component_Collider {
public:
	using Component_Collider::Component_Collider;

	float radius = 1;

	#if VISUALIZE_HITBOXES
		void VisualizeHitbox();
	#endif

protected:
	std::shared_ptr<IShape2D> GetShape() override;
	void UpdatePosition() override;

private:
	std::shared_ptr<Circle2D> shape = std::make_shared<Circle2D>();
};

