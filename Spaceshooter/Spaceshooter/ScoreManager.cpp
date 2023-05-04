// ScoreManager.cpp
// Krystof Hruby
// 2023

#include "ScoreManager.h"

bool ScoreManager::ReachedGoal() const {
	return this->score >= this->goal;
}
