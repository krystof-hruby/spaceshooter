// UUID.cpp
// Krystof Hruby
// 2023

#include <random>

#include "UUID.h"

unsigned int UUID::last_uuid = 0;

UUID::UUID() {
	UUID::last_uuid++;
	this->uuid = last_uuid;
}