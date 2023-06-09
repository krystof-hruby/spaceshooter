// Component_RectangleCollider.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_Collider.h"

// Collider with a rectangular shape (can be rotated).
class Component_RectangleCollider : public Component_Collider {
public:
	using Component_Collider::Component_Collider;

	float width = 1;
	float height = 1;

	#if VISUALIZE_HITBOXES
		// Displays a non-angled rectangle because apparently only non-angled rectangle can be filled with colour.
		// The actual hitboxes are angled according to transform rotation.
		void VisualizeHitbox();
	#endif

protected:
	std::shared_ptr<IShape2D> GetShape() override;
	void UpdatePosition() override;

private:
	std::shared_ptr<AngledRectangle2D> shape = std::make_shared<AngledRectangle2D>();
};

