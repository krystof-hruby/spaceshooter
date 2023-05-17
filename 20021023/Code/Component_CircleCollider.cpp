// Component_CircleCollider.cpp
// Krystof Hruby
// 2023

#include "Component_CircleCollider.h"

std::shared_ptr<IShape2D> Component_CircleCollider::GetShape() {
	return this->shape;
}

void Component_CircleCollider::UpdatePosition() {
	Vector2D collider_position = this->GetWorldPosition();

	this->shape->PlaceAt(collider_position, this->radius);
}

#if VISUALIZE_HITBOXES
void Component_CircleCollider::VisualizeHitbox() {
	MyDrawEngine::GetInstance()->FillCircle(this->GetGameObject()->GetComponent<Component_Transform>()->position + this->position_offset, this->radius, MyDrawEngine::GREEN);
}
#endif