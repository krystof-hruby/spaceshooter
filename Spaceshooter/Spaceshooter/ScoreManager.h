// ScoreManager.h
// Krystof Hruby
// 2023

#pragma once

class ScoreManager {
public:
	int goal = 1;
	int score = 0;

	bool ReachedGoal() const;
};

