#pragma once
#include "../Direction.h"
#include "../Point2.h"
#include "../LevelData.h"

namespace EasterPanic
{
	namespace Level_002
	{
		constexpr const uint8_t MaxActions = 8;
		constexpr const uint8_t PlayerX = 3;
		constexpr const uint8_t PlayerY = 3;
		constexpr const Direction PlayerDirection = Direction::North;

		const uint8_t TileData[] PROGMEM =
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

		const PointU8 Collectables[] PROGMEM =
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

		constexpr const LevelData Data = LevelData(MaxActions, Entity(PlayerX, PlayerY, PlayerDirection), TileData, LevelCollectableData(Collectables));
	}
}