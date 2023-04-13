// Component_CircleCollider.cpp
// Krystof Hruby
// 2023

#include "Component_CircleCollider.h"

#if VISUALIZE_HITBOXES
	#include "Component_Transform.h"
	#include "GameObject.h"
	#include "mydrawengine.h"
#endif

std::shared_ptr<IShape2D> Component_CircleCollider::GetShape() {
	return this->shape;
}

void Component_CircleCollider::UpdatePosition() {
	Vector2D collider_position = this->GetWorldPosition();

	this->shape->PlaceAt(collider_position, this->radius);
}

#if VISUALIZE_HITBOXES
void Component_CircleCollider::VisualizeHitbox() {
	MyDrawEngine::GetInstance()->FillCircle(this->GetGameObject()->GetComponent<Component_Transform>()->position, this->radius, MyDrawEngine::GREEN);
}
#endif