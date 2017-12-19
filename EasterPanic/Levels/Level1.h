#pragma once
#include "../Direction.h"
#include "../Collectable.h"

constexpr const uint8_t Level1MaxActions = 8;
constexpr const uint8_t Level1PlayerX = 2;
constexpr const uint8_t Level1PlayerY = 2;
constexpr const Direction Level1PlayerDirection = Direction::East;

const uint8_t Level1TileData[] PROGMEM =
{
	0xFF, // 11111111
	0xFF, // 11111111
	0xC3, // 11000011
	0xDB, // 11011011
	0xDB, // 11011011
	0xC3, // 11000011
	0xFF, // 11111111
	0xFF, // 11111111
};

const Collectable Level1Collectables[] PROGMEM =
{
	Collectable(5, 2),
	Collectable(2, 5),
	Collectable(5, 5),
};