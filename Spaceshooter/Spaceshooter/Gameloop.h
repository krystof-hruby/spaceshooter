// Gameloop.h
// Krystof Hruby
// 2023

#pragma once

class Gameloop {
public:
	static void Start();
	static void Update(double frame_time);
	static void End();
};
