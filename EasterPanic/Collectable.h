#pragma once

class Collectable
{
public:
	uint8_t x;
	uint8_t y;

public:
	Collectable(void) = default;
	constexpr Collectable(uint8_t x, uint8_t y) : x(x), y(y) {}
	
};