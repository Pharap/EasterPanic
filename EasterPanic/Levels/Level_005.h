#pragma once
#include "../Direction.h"
#include "../Point2.h"
#include "../LevelData.h"

namespace EasterPanic
{
	namespace Level_005
	{
		constexpr const uint8_t MaxActions = 12;
		constexpr const uint8_t PlayerX = 2;
		constexpr const uint8_t PlayerY = 2;
		constexpr const Direction PlayerDirection = Direction::West;

		const uint8_t TileData[] PROGMEM =
		{
			0x18, // 00011000
			0x5A, // 01011010
			0x00, // 00000000
			0xDB, // 11011011
			0xDB, // 11011011
			0x00, // 00000000
			0x5A, // 01011010
			0x18, // 00011000
		};

		const PointU8 Collectables[] PROGMEM =
		{
			PointU8(0, 0),
			PointU8(7, 0),
			PointU8(0, 7),
			PointU8(7, 7),
			
			//PointU8(2, 2),
			PointU8(5, 2),
			PointU8(2, 5),
			PointU8(5, 5),
		};

		constexpr const LevelData Data = LevelData(MaxActions, Entity(PlayerX, PlayerY, PlayerDirection), TileData, LevelCollectableData(Collectables));
	}
}