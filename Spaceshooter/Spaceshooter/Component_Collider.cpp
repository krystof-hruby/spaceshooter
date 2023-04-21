// Component_Collider.cpp
// Krystof Hruby
// 2023

#include "Component_Collider.h"

#include "GameObject.h"
#include "Component_Transform.h"

#include "Logging.h" // TODO: remove

void Component_Collider::HandleCollision(std::shared_ptr<Component_Collider> other) {
	if (!this->in_collision && this->CollidesWith(other)) {
		this->in_collision = true;
		this->OnCollisionEnter(other->GetGameObject());
		
		// Must trigger both, collisions are not checked twice.
		other->in_collision = true;
		other->OnCollisionEnter(this->GetGameObject());
	}
	else if (this->in_collision && this->CollidesWith(other)) {
		this->OnCollisionStay(other->GetGameObject());
		
		// Must trigger both, collisions are not checked twice.
		other->OnCollisionStay(this->GetGameObject());
	}
	else if (this->in_collision && !this->CollidesWith(other)) {
		this->in_collision = false;
		this->OnCollisionLeave(other->GetGameObject());

		// Must trigger both, collisions are not checked twice.
		other->in_collision = false;
		other->OnCollisionLeave(this->GetGameObject());
	}
}

bool Component_Collider::CollidesWith(std::shared_ptr<Component_Collider> other) {
	return this->GetShape()->Intersects(*(other->GetShape()));
}

Vector2D Component_Collider::GetWorldPosition() {
	return this->GetGameObject()->GetComponent<Component_Transform>()->position + this->position_offset;
}

void Component_Collider::OnCollisionEnter(std::shared_ptr<GameObject> game_object) { }

void Component_Collider::OnCollisionStay(std::shared_ptr<GameObject> game_object) { }

void Component_Collider::OnCollisionLeave(std::shared_ptr<GameObject> game_object) { }

void Component_Collider::Update() {
	this->UpdatePosition();

	#if VISUALIZE_HITBOXES
		this->VisualizeHitbox();
	#endif
}

