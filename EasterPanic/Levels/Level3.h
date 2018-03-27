#pragma once
#include "../Direction.h"
#include "../Point2.h"

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

const PointU8 Level3Collectables[] PROGMEM =
{
	PointU8(1, 2),
	PointU8(1, 5),

	PointU8(6, 2),
	PointU8(6, 5),

	PointU8(2, 1),
	PointU8(5, 1),

	PointU8(2, 6),
	PointU8(5, 6),
};