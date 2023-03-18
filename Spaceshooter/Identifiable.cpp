// Identifiable.cpp
// Krystof Hruby
// 2023

#include "Identifiable.h"

UUID Identifiable::last_uuid = 0;

Identifiable::Identifiable() {
	this->uuid = Identifiable::last_uuid;
	Identifiable::last_uuid++;
}

UUID Identifiable::GetID() {
	return this->uuid;
}
