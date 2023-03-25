// Identifiable.cpp
// Krystof Hruby
// 2023

#include "Identifiable.h"

ObjectUUID Identifiable::last_uuid = 0;

Identifiable::Identifiable() {
	this->uuid = Identifiable::last_uuid;
	Identifiable::last_uuid++;
}

ObjectUUID Identifiable::GetID() const {
	return this->uuid;
}
