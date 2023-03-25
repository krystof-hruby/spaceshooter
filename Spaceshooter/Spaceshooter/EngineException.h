// EngineException.h
// Krystof Hruby
// 2023

#pragma once

#include <exception>
#include <string>

// Throw this when required.
class EngineException : public std::exception {
private:
	std::string message;

public:
	explicit EngineException(std::string message);
	
	// Logs the message (if loggind enabled).
	const char* what() const throw();
};

