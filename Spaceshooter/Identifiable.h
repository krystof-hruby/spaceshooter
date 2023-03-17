// Identifiable.h
// Krystof Hruby
// 2023

#pragma once

#include "UUID.h"

class Identifiable {
private:
	UUID id;

public:
	UUID GetID();
	bool IsID(UUID id);
};

