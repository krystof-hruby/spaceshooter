// Component_Collider.cpp
// Krystof Hruby
// 2023

#include "Component_Collider.h"

#include "GameObject.h"

void Component_Collider::HandleCollision(std::shared_ptr<Component_Collider> other) {
	if (!this->in_collision && this->CollidesWith(other)) {
		this->OnCollisionEnter(other->game_object);
		this->in_collision = true;
	}
	else if (this->in_collision && this->CollidesWith(other)) {
		this->OnCollisionStay(other->game_object);
	}
	else if (this->in_collision && !this->CollidesWith(other)) {
		this->OnCollisionLeave(other->game_object);
		this->in_collision = false;
	}
}

bool Component_Collider::CollidesWith(std::shared_ptr<Component_Collider> other) {
	return this->Shape()->Intersects(*(other->Shape()));
}

void Component_Collider::OnCollisionEnter(std::shared_ptr<GameObject> other) { }

void Component_Collider::OnCollisionStay(std::shared_ptr<GameObject> other) { }

void Component_Collider::OnCollisionLeave(std::shared_ptr<GameObject> other) { }

