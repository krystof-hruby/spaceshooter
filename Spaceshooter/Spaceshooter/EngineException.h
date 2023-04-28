// EngineException.h
// Krystof Hruby
// 2023

#pragma once

#include <string>

// Throw this when required.
class EngineException : public std::exception {
public:
	explicit EngineException(std::string message);
	const char* what() const throw();

private:
	std::string message;
};

