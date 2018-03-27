#pragma once
#include "../Direction.h"
#include "../Point2.h"
#include "../LevelData.h"

namespace EasterPanic
{
	namespace Level_000
	{
		constexpr const uint8_t MaxActions = 4;
		constexpr const uint8_t PlayerX = 3;
		constexpr const uint8_t PlayerY = 3;
		constexpr const Direction PlayerDirection = Direction::North;

		const uint8_t TileData[] PROGMEM =
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

		const PointU8 Collectables[] PROGMEM =
		{
			PointU8(2, 2),
		};

		constexpr const LevelData Data = LevelData(MaxActions, Entity(PlayerX, PlayerY, PlayerDirection), TileData, LevelCollectableData(Collectables));
	}
}