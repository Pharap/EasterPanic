#pragma once

#include "Entity.h"
#include "LevelCollectableData.h"

class LevelData
{
public:
	uint8_t maxActions;
	Entity playerStart;
	uint8_t const * tileData;
	LevelCollectableData collectableData;

public:
	LevelData(void) = default;
	
	constexpr LevelData(uint8_t maxActions, Entity playerStart, uint8_t const * tileData, LevelCollectableData collectableData)
		: maxActions(maxActions), playerStart(playerStart), tileData(tileData), collectableData(collectableData)
	{
	}
};