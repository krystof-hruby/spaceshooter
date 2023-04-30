// Component_Collider.cpp
// Krystof Hruby
// 2023

#include "Component_RectangleCollider.h"

#include "Component_Transform.h"
#include "GameObject.h"
#include "mydrawengine.h"

std::shared_ptr<IShape2D> Component_RectangleCollider::GetShape() {
	return this->shape;
}

void Component_RectangleCollider::UpdatePosition() {
	this->shape->SetCentre(this->GetWorldPosition());
	this->shape->SetDimensions(this->height, this->width);
	this->shape->SetAngle(this->GetGameObject()->GetComponent<Component_Transform>()->rotation);
}

#if VISUALIZE_HITBOXES
void Component_RectangleCollider::VisualizeHitbox() {
	// Calculate rectangle corners.
	Vector2D collider_position = this->GetWorldPosition() + this->position_offset;
	Vector2D left_bottom(collider_position.XValue - (this->width / 2), collider_position.YValue - (this->height / 2));
	Vector2D right_top(collider_position.XValue + (this->width / 2), collider_position.YValue + (this->height / 2));

	Rectangle2D rectangle;
	rectangle.PlaceAt(left_bottom, right_top);

	MyDrawEngine::GetInstance()->FillRect(rectangle, MyDrawEngine::GREEN);
}
#endif