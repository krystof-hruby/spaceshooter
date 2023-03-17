// UUID.h
// Krystof Hruby
// 2023

#pragma once

#include <string>

// Provides universally unique identifiers
class UUID {
private:
	static unsigned int last_uuid;
	unsigned int uuid;
public:
	UUID();
	bool operator==(UUID uuid);
	std::string AsString();
};

