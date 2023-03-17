// Identifiable.cpp
// Krystof Hruby
// 2023

#include "Identifiable.h"

UUID Identifiable::GetID() {
	return this->id;
}

bool Identifiable::IsID(UUID id) {
	return this->id == id;
}