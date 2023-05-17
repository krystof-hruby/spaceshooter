// Identifiable.h
// Krystof Hruby
// 2023

#pragma once

#include <cstdint>

// Object Universally Unique Identifier
typedef std::uint32_t ObjectUUID;

// Provides object identification by UUID.
class Identifiable {
public:
	// Returns the id of this object.
	ObjectUUID GetID() const;

protected:
	Identifiable();

private:
	static ObjectUUID last_uuid;
	ObjectUUID uuid;
};

