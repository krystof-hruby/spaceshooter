// Logging.h
// Krystof Hruby
// 2023

#pragma once

#include "Debugging.h"

#if LOGGING_ENABLED
	#include <fstream>
	#include <memory>
	
	extern std::shared_ptr<std::ofstream> log_file;
	// Logs a message to a log file "debug.log".
	#define LOG(message) (*log_file) << message << std::endl
#else
	#define LOG(Message)
#endif
