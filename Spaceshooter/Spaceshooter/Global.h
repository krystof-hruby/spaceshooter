// Global.h
// Krystof Hruby
// 2023

#pragma once

// DEBUGGING:

#ifndef LOGGING_ENABLED
	#define LOGGING_ENABLED true
#endif

// GLOBAL VALUES:

// Provides delta time.
class Time {
public:
	// Provides delta time between last two frames.
	static double delta_time;
};
