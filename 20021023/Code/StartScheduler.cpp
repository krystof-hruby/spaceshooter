// StartScheduler.cpp
// Krystof Hruby
// 2023

#include "StartScheduler.h"

void StartScheduler::ScheduleComponent(std::shared_ptr<Component> component) {
	this->scheduled_components.push(component);
}

void StartScheduler::StartScheduledComponents() {
	// Iterate over all components scheduled to start and call Start method.
	while (!this->scheduled_components.empty()) {
		auto component = this->scheduled_components.front();

		if (component->is_active)
			component->Start();

		component->started = true;

		this->scheduled_components.pop();
	}
}
