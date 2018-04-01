#pragma once

#include "ActionId.h"

class Action
{
private:
	ActionId id = ActionId::None;
	uint8_t argument = 1;

public:
	constexpr Action(void) = default;
	constexpr Action(ActionId id) : id(id), argument(1) {}
	constexpr Action(ActionId id, uint8_t argument) : id(id), argument(argument) {}
	
	ActionId & getId(void) { return this->id; }
	constexpr const ActionId & getId(void) const { return this->id; }
	
	uint8_t & getArgument(void) { return this->argument; }
	constexpr const uint8_t & getArgument(void) const { return this->argument; }
};