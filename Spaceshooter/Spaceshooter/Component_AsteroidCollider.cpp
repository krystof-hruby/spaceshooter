// Component_AsteroidCollider.cpp
// Krystof Hruby
// 2023

#include "Component_AsteroidCollider.h"
#include "GameObject.h"
#include "Logging.h" // TODO: remove

void Component_AsteroidCollider::OnCollisionEnter(std::shared_ptr<GameObject> other) {
	if (other->tag != "Player")
		return;

}

void Component_AsteroidCollider::OnCollisionStay(std::shared_ptr<GameObject> other) {
	if (other->tag != "Player")
		return;
	
}

void Component_AsteroidCollider::OnCollisionLeave(std::shared_ptr<GameObject> other) {
	if (other->tag != "Player")
		return;
	
}
