#include "../LevelData.h"

#include "Level0.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

const LevelData Levels[] PROGMEM =
{
	LevelData(Level0MaxActions, Entity(Level0PlayerX, Level0PlayerY, Level0PlayerDirection), Level0TileData, LevelCollectableData(Level0Collectables)),
	LevelData(Level1MaxActions, Entity(Level1PlayerX, Level1PlayerY, Level1PlayerDirection), Level1TileData, LevelCollectableData(Level1Collectables)),
	LevelData(Level2MaxActions, Entity(Level2PlayerX, Level2PlayerY, Level2PlayerDirection), Level2TileData, LevelCollectableData(Level2Collectables)),
	LevelData(Level3MaxActions, Entity(Level3PlayerX, Level3PlayerY, Level3PlayerDirection), Level3TileData, LevelCollectableData(Level3Collectables)),
	//LevelData(Level4MaxActions, Entity(Level4PlayerX, Level4PlayerY, Level4PlayerDirection), Level4TileData, LevelCollectableData(Level4Collectables)),
};