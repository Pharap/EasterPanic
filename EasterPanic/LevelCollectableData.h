#pragma once

#include "Collectable.h"

class LevelCollectableData
{
public:
	uint8_t collectableCount;
	Collectable const * collectables;
	
public:
	LevelCollectableData(void) = default;
	
	constexpr LevelCollectableData(uint8_t collectableCount, Collectable const * collectables)
		: collectableCount(collectableCount), collectables(collectables)
	{
	}
		
	template< size_t size >
	constexpr LevelCollectableData(Collectable const (&collectables)[size])
		: collectableCount(size), collectables(collectables)
	{
	}

	constexpr LevelCollectableData(Collectable const (&)[0])
		: collectableCount(0), collectables(nullptr)
	{
	}
};