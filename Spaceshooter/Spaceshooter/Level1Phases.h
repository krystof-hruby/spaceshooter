// Level1Phases.h
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

class Level1Phase_Preparation : public Level1Phase {
public:
	void Play(std::shared_ptr<Component_Level1Manager> level1manager) override;

private:
	float preparation_time = 0;
};

class Level1Phase_Intro : public Level1Phase {
public:
	void Play(std::shared_ptr<Component_Level1Manager> level1manager);

private:
	float player_spawn_time = 0;
	bool player_spawned = false;
};

class Level1Phase_Tutorial : public Level1Phase {
public:
	void Play(std::shared_ptr<Component_Level1Manager> level1manager);

private:
	float asteroids_spawn_time = 0;
	bool commander_despawned = false;
	bool asteroids_spawned = false;
};

class Level1Phase_Gameplay : public Level1Phase {
public:
	void Play(std::shared_ptr<Component_Level1Manager> level1manager) override;

private:
	float gameplay_time = 0;

	bool passed14 = false;
	bool passed12 = false;
	bool passed34 = false;
};

class Level1Phase_Outro : public Level1Phase {
public:
	void Play(std::shared_ptr<Component_Level1Manager> level1manager) override;

private:
};