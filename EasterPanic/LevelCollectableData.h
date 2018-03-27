#pragma once

#include "Point2.h"

class LevelCollectableData
{
public:
	uint8_t collectableCount;
	PointU8 const * collectables;
	
public:
	LevelCollectableData(void) = default;
	
	constexpr LevelCollectableData(uint8_t collectableCount, PointU8 const * collectables)
		: collectableCount(collectableCount), collectables(collectables)
	{
	}
		
	template< size_t size >
	constexpr LevelCollectableData(PointU8 const (&collectables)[size])
		: collectableCount(size), collectables(collectables)
	{
	}

	constexpr LevelCollectableData(PointU8 const (&)[0])
		: collectableCount(0), collectables(nullptr)
	{
	}
};