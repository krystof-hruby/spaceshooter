// StartScheduler.h
// Krystof Hruby
// 2023

#pragma once

#include <queue>

#include "Component.h"

// Manages Start methods of components.
class StartScheduler final {
public:
	// Schedules component for Start next frame.
	void ScheduleComponent(std::shared_ptr<Component> component);

	// Starts all components scheduled to be started.
	void StartScheduledComponents();

private:
	std::queue<std::shared_ptr<Component>> scheduled_components;
};

