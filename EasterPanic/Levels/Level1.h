#pragma once
#include "../Direction.h"
#include "../Point2.h"

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

const PointU8 Level1Collectables[] PROGMEM =
{
	PointU8(5, 2),
	PointU8(2, 5),
	PointU8(5, 5),
};