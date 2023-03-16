// Logging.cpp
// Krystof Hruby
// 2023

#include "Logging.h"

#if LOGGING
	std::shared_ptr<std::ofstream> log_file = std::make_shared<std::ofstream>("debug.log");
#endif