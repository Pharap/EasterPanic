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
	// Layout constants
	const auto centreY = CalculateCentreY(FontLineHeight);
	const auto singleMargin = 2;
	const auto doubleMargin = singleMargin * 2;
	const auto lineHeight = FontLineHeight + doubleMargin;
	
	auto arduboy = machine.getContext().arduboy;
	
	// Draw level names, including previous two and next two
	for(int8_t i = -2; i <= +2; ++i)
	{
		const int8_t index = this->index + i; // int8_t is cheaper than integer promotion
		const size_t levelCount = ArrayLength(Levels); // Caching saves 2 bytes
		if(index >= 0 && static_cast<size_t>(index) < levelCount)
		{
			arduboy.setCursor(doubleMargin, centreY + (lineHeight * i));
			arduboy.print(FlashString(StringLevelHeading));
			arduboy.print(index);
		}
	}
	
	// Draw selector
	arduboy.drawRect(0 + singleMargin, centreY - singleMargin, Arduboy::ScreenWidth - doubleMargin, lineHeight, Arduboy::ColourWhite);
}