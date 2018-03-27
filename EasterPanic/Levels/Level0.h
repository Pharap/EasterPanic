#pragma once
#include "../Direction.h"
#include "../Point2.h"

constexpr const uint8_t Level0MaxActions = 4;
constexpr const uint8_t Level0PlayerX = 3;
constexpr const uint8_t Level0PlayerY = 3;
constexpr const Direction Level0PlayerDirection = Direction::North;

const uint8_t Level0TileData[] PROGMEM =
{
	0xFF, // 11111111
	0xFF, // 11111111
	0xDF, // 11011111
	0xCF, // 11001111
	0xFF, // 11111111
	0xFF, // 11111111
	0xFF, // 11111111
	0xFF, // 11111111
};

const PointU8 Level0Collectables[] PROGMEM =
{
	PointU8(2, 2),
};