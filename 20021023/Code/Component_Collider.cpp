// Component_Collider.cpp
// Krystof Hruby
// 2023

#include "Component_Collider.h"

#include "Component_Transform.h"
#include "GameObject.h"

void Component_Collider::HandleCollision(std::shared_ptr<Component_Collider> other) {
	ObjectUUID other_id = other->GetGameObject()->GetID();
	
	if (!this->IsInCollisionWith(other_id) && this->CollidesWith(other)) {
		this->in_collision_with.insert(other_id);
		this->OnCollisionEnter(other->GetGameObject());
		
		// Must trigger both, collisions are not checked twice.
		other->in_collision_with.insert(other_id);
		other->OnCollisionEnter(this->GetGameObject());
	}
	else if (this->IsInCollisionWith(other_id) && this->CollidesWith(other)) {
		this->OnCollisionStay(other->GetGameObject());
		
		// Must trigger both, collisions are not checked twice.
		other->OnCollisionStay(this->GetGameObject());
	}
	else if (this->IsInCollisionWith(other_id) && !this->CollidesWith(other)) {
		this->in_collision_with.erase(other_id);
		this->OnCollisionLeave(other->GetGameObject());

		// Must trigger both, collisions are not checked twice.
		other->in_collision_with.erase(other_id);
		other->OnCollisionLeave(this->GetGameObject());
	}
}

bool Component_Collider::IsInCollisionWith(ObjectUUID other_id) {
	return this->in_collision_with.find(other_id) != this->in_collision_with.end();
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

void Component_Collider::Start() {
	this->UpdatePosition();

	#if VISUALIZE_HITBOXES
		this->VisualizeHitbox();
	#endif
}

void Component_Collider::Update() {
	this->UpdatePosition();

	#if VISUALIZE_HITBOXES
		this->VisualizeHitbox();
	#endif
}
