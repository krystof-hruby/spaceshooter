// BossState.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>

class Component_BossController; // Must #include Component_BossController in .cpp file.

// Abstract parent class for boss states. Override methods to provide functionality.
class BossState {
public:
	virtual void Play(std::shared_ptr<Component_BossController> boss_controller) { }

protected:
	BossState() { }
};

