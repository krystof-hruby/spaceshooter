// EngineException.cpp
// Krystof Hruby
// 2023

#include "EngineException.h"

EngineException::EngineException(std::string message) {
	this->message = message;
}

const char* EngineException::what() const throw() {
	return this->message.c_str();
}
