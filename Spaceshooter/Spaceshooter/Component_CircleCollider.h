// Component_CircleCollider.h
// Krystof Hruby
// 2023

#pragma once

#include "Component_Collider.h"

class Component_CircleCollider final : public Component_Collider {
private:
	std::shared_ptr<Circle2D> shape = std::make_shared<Circle2D>();

protected:
	std::shared_ptr<IShape2D> GetShape();

	void UpdatePosition();

public:
	using Component_Collider::Component_Collider;

	float radius = 1;

#if VISUALIZE_HITBOXES
	void VisualizeHitbox();
#endif
};

