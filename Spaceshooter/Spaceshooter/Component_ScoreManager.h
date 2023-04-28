// Component_ScoreManager.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"

class Component_ScoreManager final : public Component {
public:
	using Component::Component;
	inline bool Startable() const override { return false; }
	inline bool Updatable() const override { return false; }

	int score = 0;

	#if LOWER_GOAL
		int goal = GOAL;
	#else
		int goal = 50;
	#endif
	
	// Returns true if goal was reached.
	bool ReachedGoal() const;
};

