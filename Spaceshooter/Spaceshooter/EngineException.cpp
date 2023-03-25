// EngineException.cpp
// Krystof Hruby
// 2023

#include "EngineException.h"

#include "Logging.h"

EngineException::EngineException(std::string message) {
	this->message = message;
}

const char* EngineException::what() const throw() {
	LOG(this->message);
	return this->message.c_str();
}
