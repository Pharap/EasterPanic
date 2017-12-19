#pragma once
#include "../Direction.h"
#include "../Collectable.h"

constexpr const uint8_t Level2MaxActions = 8;
constexpr const uint8_t Level2PlayerX = 3;
constexpr const uint8_t Level2PlayerY = 3;
constexpr const Direction Level2PlayerDirection = Direction::North;

const uint8_t Level2TileData[] PROGMEM =
{
	0xFF, // 11111111
	0x83, // 10000011
	0xAB, // 10101011
	0x83, // 10000011
	0xAB, // 10101011
	0x83, // 10000011
	0xFF, // 11111111
	0xFF, // 11111111
};

const Collectable Level2Collectables[] PROGMEM =
{
	Collectable(1, 1),
	Collectable(3, 1),
	Collectable(5, 1),
	
	Collectable(1, 3),	
	Collectable(5, 3),
	
	Collectable(1, 5),
	Collectable(3, 5),
	Collectable(5, 5),
};