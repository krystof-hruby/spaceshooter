// Component_LaserController.cpp
// Krystof Hruby
// 2023

#include "Component_LaserController.h"

#include "GameObject.h"
#include "Time.h"

void Component_LaserController::Update() {
	if (this->laser_time > this->laser_period)
		this->GetGameObject()->Destroy();

	this->laser_time += (float)Time::delta_time;
}
