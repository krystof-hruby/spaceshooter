// Level1Phase.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>

class Component_Level1Manager;

class Level1Phase {
public:
	virtual void Play(std::shared_ptr<Component_Level1Manager> level1manager) { }

protected:
	Level1Phase() { }
};

