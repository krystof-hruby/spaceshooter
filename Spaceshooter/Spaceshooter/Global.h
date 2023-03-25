// Global.h
// Krystof Hruby
// 2023

#pragma once

// DEBUGGING:

#ifndef LOGGING_ENABLED
	#define LOGGING_ENABLED true
#endif

// GLOBAL VALUES:
const float SECOND = 1;

// Provides delta time.
class Time final {
public:
	// Provides delta time between last two frames.
	static double delta_time;
};
