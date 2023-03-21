// Identifiable.h
// Krystof Hruby
// 2023

#pragma once

#include <cstdint>
#include <string>

#ifndef ObjectUUID
	// Object Universally Unique Identifier
	#define ObjectUUID std::uint32_t
#endif

// Provides object identification by UUID.
class Identifiable {
private:
	static ObjectUUID last_uuid;
	ObjectUUID uuid;

protected:
	Identifiable();

public:
	// Returns the id of this object.
	ObjectUUID GetID();
};

