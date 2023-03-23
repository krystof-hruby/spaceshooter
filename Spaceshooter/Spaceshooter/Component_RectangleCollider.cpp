// Component_Collider.cpp
// Krystof Hruby
// 2023

#include "Component_RectangleCollider.h"

std::shared_ptr<IShape2D> Component_RectangleCollider::GetShape() {
	return this->shape;
}

void Component_RectangleCollider::UpdatePosition() {
	Vector2D collider_position = this->GetWorldPosition();
	
	// Y goes positive towards top.
	float top = collider_position.YValue + (this->height / 2);
	float bottom = collider_position.YValue - (this->height / 2);
	
	// X goes positive towards right.
	float left = collider_position.XValue - (this->width / 2);
	float right = collider_position.XValue + (this->width / 2);

	this->shape->PlaceAt(top, bottom, left, right);
}
