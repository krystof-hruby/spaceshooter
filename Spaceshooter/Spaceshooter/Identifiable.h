// Identifiable.h
// Krystof Hruby
// 2023

#pragma once

#include <cstdint>
#include <string>

#ifndef UUID
	#define UUID std::uint32_t
#endif

class Identifiable {
private:
	static UUID last_uuid;
	UUID uuid;

protected:
	Identifiable();

public:
	UUID GetID();
};

