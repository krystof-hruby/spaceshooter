// Component_PlayerBulletController.cpp
// Krystof Hruby
// 2023

#include "Component_PlayerBulletController.h"

#include "Component_Transform.h"
#include "GameObject.h"
#include "Global.h"

void Component_PlayerBulletController::Update() {
	this->game_object->GetComponent<Component_Transform>()->position += this->direction * this->speed * Time::delta_time;
}