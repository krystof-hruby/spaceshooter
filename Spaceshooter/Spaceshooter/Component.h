// Component.h
// Krystof Hruby
// 2023

#pragma once

#include <memory>

#include "Identifiable.h"

class GameObject;

class Component : public Identifiable {
protected:
	Component(std::shared_ptr<GameObject> game_object);
	std::shared_ptr<GameObject> game_object;

public:
	std::shared_ptr<GameObject> GetGameObject();
	virtual void Start();
	virtual void Update();
};

