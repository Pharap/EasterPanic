#include "LevelSelectState.h"

#include "Utils.h"
#include "Levels.h"
#include "Strings.h"

void LevelSelectState::update(StateMachine & machine)
{
	auto arduboy = machine.getContext().arduboy;
	
	if(arduboy.justPressed(Arduboy::ButtonUp))
	{
		if(this->index > 0)
			--this->index;
	}
	
	if(arduboy.justPressed(Arduboy::ButtonDown))
	{
		if(this->index < ArrayLength(Levels) - 1)
			++this->index;	
	}
	
	if(arduboy.justPressed(Arduboy::ButtonA))
	{
		machine.getContext().selectedLevel = this->index;
		machine.changeState(StateId::Gameplay);
		return;
	}
	
	if(arduboy.justPressed(Arduboy::ButtonB))
	{
		machine.changeState(StateId::TitleScreen);
		return;
	}
}

void LevelSelectState::render(StateMachine & machine)
{
	const auto centreY = CalculateCentreY(FontLineHeight);
	const auto levelCount = ArrayLength(Levels);
	const auto lineHeight = FontLineHeight + 4;
	
	auto arduboy = machine.getContext().arduboy;
	
	arduboy.setCursor(4, centreY);
	arduboy.print(FlashString(StringLevelHeading));
	arduboy.print(this->index);
	
	// ToDo: tidy up, make a for loop or something
	if(this->index  > 0)
	{	
		arduboy.setCursor(4, centreY - (lineHeight * 1));
		arduboy.print(FlashString(StringLevelHeading));
		arduboy.print(this->index - 1);	
	}
	if(this->index  > 1)
	{
		arduboy.setCursor(4, centreY - (lineHeight * 2));
		arduboy.print(FlashString(StringLevelHeading));
		arduboy.print(this->index - 2);
	}
	if(this->index > 2)
	{
		arduboy.setCursor(4, centreY - (lineHeight * 3));
		arduboy.print(FlashString(StringLevelHeading));
		arduboy.print(this->index - 3);	
	}
	
	if(this->index + 1 < levelCount)
	{	
		arduboy.setCursor(4, centreY + (lineHeight * 1));
		arduboy.print(FlashString(StringLevelHeading));
		arduboy.print(this->index + 1);
	}
	if(this->index + 2 < levelCount)
	{
		arduboy.setCursor(4, centreY + (lineHeight * 2));
		arduboy.print(FlashString(StringLevelHeading));
		arduboy.print(this->index + 2);
	}
	if(this->index + 3 < levelCount)
	{
		arduboy.setCursor(4, centreY + (lineHeight * 3));
		arduboy.print(FlashString(StringLevelHeading));
		arduboy.print(this->index + 3);
	}
	
	arduboy.drawRect(2, centreY - 2, Arduboy::ScreenWidth - 4, FontLineHeight + 4, Arduboy::ColourWhite);
}