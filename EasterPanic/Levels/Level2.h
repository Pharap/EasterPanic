#pragma once
#include "../Direction.h"
#include "../Point2.h"

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

const PointU8 Level2Collectables[] PROGMEM =
{
	PointU8(1, 1),
	PointU8(3, 1),
	PointU8(5, 1),

	PointU8(1, 3),
	PointU8(5, 3),

	PointU8(1, 5),
	PointU8(3, 5),
	PointU8(5, 5),
};