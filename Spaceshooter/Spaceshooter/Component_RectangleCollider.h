// Component_RectangleCollider.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_Collider.h"

class Component_RectangleCollider final : public Component_Collider {
private:
	std::shared_ptr<Rectangle2D> shape = std::make_shared<Rectangle2D>();

protected:
	std::shared_ptr<IShape2D> GetShape();

	void UpdatePosition();

public:
	using Component_Collider::Component_Collider;

	float width = 1;
	float height = 1;

#if VISUALIZE_HITBOXES
	void VisualizeHitbox();
#endif
};

