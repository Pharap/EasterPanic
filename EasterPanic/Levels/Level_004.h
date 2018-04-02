#pragma once
#include "../Direction.h"
#include "../Point2.h"
#include "../LevelData.h"

namespace EasterPanic
{
	namespace Level_004
	{
		constexpr const uint8_t MaxActions = 12;
		constexpr const uint8_t PlayerX = 2;
		constexpr const uint8_t PlayerY = 3;
		constexpr const Direction PlayerDirection = Direction::North;

		const uint8_t TileData[] PROGMEM =
		{
			0x00, // 00000000
			0x38, // 00111000
			0x44, // 01000100
			0x52, // 01010010
			0x4A, // 01001010
			0x22, // 00100010
			0x1C, // 00011100
			0x00, // 00000000
		};

		const PointU8 Collectables[] PROGMEM =
		{
			PointU8(2, 2),
			PointU8(4, 3),
			PointU8(3, 4),
			PointU8(5, 5),
		};

		constexpr const LevelData Data = LevelData(MaxActions, Entity(PlayerX, PlayerY, PlayerDirection), TileData, LevelCollectableData(Collectables));
	}
}