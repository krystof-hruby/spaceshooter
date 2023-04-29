// BossState.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>

class Component_BossController;

class BossState {
public:
	virtual void Play(std::shared_ptr<Component_BossController> boss_controller) = 0;

protected:
	BossState() { }
};

