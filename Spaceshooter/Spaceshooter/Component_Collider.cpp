// Component_Collider.cpp
// Krystof Hruby
// 2023

#include "Component_Collider.h"

#include "GameObject.h"
#include "Component_Transform.h"

void Component_Collider::HandleCollision(std::shared_ptr<Component_Collider> other) {
	if (!this->in_collision && this->CollidesWith(other)) {
		this->in_collision = true;
		
		if (this->OnCollisionEnter)
			this->OnCollisionEnter(other->game_object);
		
		// Must trigger both, collisions are not checked twice.
		if (other->OnCollisionEnter)
			other->OnCollisionEnter(this->game_object);
	}
	else if (this->in_collision && this->CollidesWith(other)) {
		if (this->OnCollisionStay)
			this->OnCollisionStay(other->game_object);
		
		// Must trigger both, collisions are not checked twice.
		if (other->OnCollisionStay)
			other->OnCollisionStay(this->game_object);
	}
	else if (this->in_collision && !this->CollidesWith(other)) {
		this->in_collision = false;
		
		if (this->OnCollisionLeave)
			this->OnCollisionLeave(other->game_object);

		// Must trigger both, collisions are not checked twice.
		if (other->OnCollisionLeave)
			other->OnCollisionLeave(this->game_object);
	}
}

bool Component_Collider::CollidesWith(std::shared_ptr<Component_Collider> other) {
	return this->GetShape()->Intersects(*(other->GetShape()));
}

void Component_Collider::SetOnCollisionEnter(std::function<void(std::shared_ptr<GameObject>)> on_collision_enter) {
	this->OnCollisionEnter = on_collision_enter;
}

void Component_Collider::SetOnCollisionStay(std::function<void(std::shared_ptr<GameObject>)> on_collision_stay) {
	this->OnCollisionStay = on_collision_stay;
}

void Component_Collider::SetOnCollisionLeave(std::function<void(std::shared_ptr<GameObject>)> on_collision_leave) {
	this->OnCollisionLeave = on_collision_leave;

}

Vector2D Component_Collider::GetWorldPosition() const {
	return this->game_object->GetComponent<Component_Transform>()->position + this->position_offset;
}

void Component_Collider::Update() {
	this->UpdatePosition();
}

