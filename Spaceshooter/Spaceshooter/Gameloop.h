// Gameloop.h
// Krystof Hruby
// 2023

#pragma once

// Controls and updates the game.
class Gameloop {
public:
	// Called when starting the game.
	static void Start();

	// Called every frame.
	// Parameter frame_time comes from gamecode.cpp from the Shell.
	static void Update(double frame_time);
	
	// Called when returning to main menu.
	static void End();
};
