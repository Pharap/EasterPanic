#pragma once
#include "../Direction.h"
#include "../Collectable.h"

constexpr const uint8_t Level3MaxActions = 12;
constexpr const uint8_t Level3PlayerX = 2;
constexpr const uint8_t Level3PlayerY = 2;
constexpr const Direction Level3PlayerDirection = Direction::West;

const uint8_t Level3TileData[] PROGMEM =
{
	0xFF, // 11111111
	0xC3, // 11000011
	0x81, // 10000001
	0x81, // 10000001
	0x81, // 10000001
	0x81, // 10000001
	0xC3, // 11000011
	0xFF, // 11111111
};

const Collectable Level3Collectables[] PROGMEM =
{
	Collectable(1, 2),
	Collectable(1, 5),
	
	Collectable(6, 2),
	Collectable(6, 5),
	
	Collectable(2, 1),
	Collectable(5, 1),
	
	Collectable(2, 6),
	Collectable(5, 6),
};