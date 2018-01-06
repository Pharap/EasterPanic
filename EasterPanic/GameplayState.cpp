#include "GameplayState.h"

#include "Images.h"
#include "Strings.h"
#include "Utils.h"
#include "Levels.h"
#include "LevelData.h"
#include "TileLoader.h"

void GameplayState::activate(StateMachine & machine)
{
	auto selectedLevel = machine.getContext().selectedLevel;
	
	this->loadLevel(selectedLevel);
	
	this->state = StateType::Options;
}

void GameplayState::update(StateMachine & machine)
{
	auto arduboy = machine.getContext().arduboy;

	// ToDo: break this out into its own StateMachine
	switch(this->state)
	{
		case StateType::EditingActionList:
		{
			this->updateEditingActionList(machine);
			break;
		}
		case StateType::EditingCurrentAction:
		{
			this->updateEditingCurrentAction(machine);
			break;
		}
		case StateType::RunningActions:
		{
			this->updateRunningActions(machine);
			break;
		}
		case StateType::Error:
		{
			this->updateError(machine);
			break;
		}
		case StateType::Success:
		{
			this->updateSuccess(machine);
			break;
		}
		case StateType::Options:
		{
			this->updateOptions(machine);
			break;
		}
		case StateType::Quit:
		{
			machine.changeState(StateId::LevelSelect);
			break;
		}
		default:
		{
			break;
		}
	}
}

void GameplayState::render(StateMachine & machine)
{
	auto arduboy = machine.getContext().arduboy;

	renderPlayfield(machine);

	// ToDo: break this out into its own StateMachine
	switch(this->state)
	{
		case StateType::EditingActionList:
		{
			this->renderEditingActionList(machine);
			break;
		}
		case StateType::EditingCurrentAction:
		{
			this->renderEditingCurrentAction(machine);
			break;
		}
		case StateType::RunningActions:
		{
			this->renderRunningActions(machine);
			break;
		}
		case StateType::Error:
		{
			this->renderError(machine);
			break;
		}
		case StateType::Success:
		{
			this->renderSuccess(machine);
			break;
		}
		case StateType::Options:
		{
			this->renderOptions(machine);
			break;
		}
		case StateType::Quit:
		{
			break;
		}
		default:
		{
			break;
		}
	}
}

//
// State::Error
//

void GameplayState::updateError(StateMachine & machine)
{
	auto arduboy = machine.getContext().arduboy;

	if (arduboy.justPressed(Arduboy::ButtonA))
	{
		this->state = StateType::EditingActionList;
	}
}

const char * GameplayState::getErrorStringLine0(ErrorType type)
{
	return ProgmemRead<const char *>(&ErrorStringsLine0[static_cast<uint8_t>(type)]);
}

const char * GameplayState::getErrorStringLine1(ErrorType type)
{
	return ProgmemRead<const char *>(&ErrorStringsLine1[static_cast<uint8_t>(type)]);
}

void GameplayState::renderError(StateMachine & machine)
{
	auto arduboy = machine.getContext().arduboy;

	auto errorLine0 = getErrorStringLine0(this->error);
	auto errorLine1 = getErrorStringLine1(this->error);

	auto errorString0Width = ProgmemStringWidth(errorLine0);
	auto errorString1Width = ProgmemStringWidth(errorLine1);

	auto maxWidth = max(errorString0Width, errorString1Width);

	auto messageY = CalculateCentreY(StringHeight(3));

	{
		auto rectX = CalculateCentreX(maxWidth) - 2;
		auto rectY = messageY - 2;
		auto rectWidth = maxWidth + 4;
		auto rectHeight = StringHeight(3) + 4;

		arduboy.fillRect(rectX, rectY, rectWidth, rectHeight, Arduboy::ColourBlack);
		arduboy.drawRect(rectX, rectY, rectWidth, rectHeight, Arduboy::ColourWhite);
	}

	{
		auto messageX = CalculateCentreX(StringWidth(StringErrorHeading));
		arduboy.setCursor(messageX, messageY);
		arduboy.print(FlashString(StringErrorHeading));
		messageY += FontLineHeight;
	}
	{
		auto messageX = CalculateCentreX(errorString0Width);
		arduboy.setCursor(messageX, messageY);
		arduboy.print(FlashString(errorLine0));
		messageY += FontLineHeight;
	}
	{
		auto messageX = CalculateCentreX(errorString1Width);
		arduboy.setCursor(messageX, messageY);
		arduboy.print(FlashString(errorLine1));
		messageY += FontLineHeight;
	}
}

//
// State::Success
//

void GameplayState::updateSuccess(StateMachine & machine)
{
	auto arduboy = machine.getContext().arduboy;

	if (arduboy.justPressed(Arduboy::ButtonA))
	{
		machine.changeState(StateId::LevelSelect);
	}
}

void GameplayState::renderSuccess(StateMachine & machine)
{
	auto arduboy = machine.getContext().arduboy;

	auto messageY = CalculateCentreY(StringHeight(1));
	auto messageX = CalculateCentreX(StringWidth(StringSuccessHeading));
	arduboy.setCursor(messageX, messageY);
	arduboy.print(FlashString(StringErrorHeading));
	{
		auto rectX = messageX - 2;
		auto rectY = messageY - 2;
		auto rectWidth = StringWidth(StringSuccessHeading) + 4;
		auto rectHeight = StringHeight(1) + 4;

		arduboy.fillRect(rectX, rectY, rectWidth, rectHeight, Arduboy::ColourBlack);
		arduboy.drawRect(rectX, rectY, rectWidth, rectHeight, Arduboy::ColourWhite);
		arduboy.setCursor(messageX, messageY);
		arduboy.print(FlashString(StringSuccessHeading));
	}
}

//
// State::Options
//

const typename GameplayState::Option GameplayState::options[] PROGMEM =
{
	Option(StateType::EditingActionList, StringEdit),
	Option(StateType::RunningActions, StringRun),
	Option(StateType::Quit, StringExit),
};

void GameplayState::updateOptions(StateMachine & machine)
{
	auto arduboy = machine.getContext().arduboy;

	if (arduboy.justPressed(Arduboy::ButtonUp))
	{
		if(this->selectedOption > 0)
			--this->selectedOption;
	}
	
	if (arduboy.justPressed(Arduboy::ButtonDown))
	{
		if(this->selectedOption < (ArrayLength(options) - 1))
			++this->selectedOption;
	}
	
	if (arduboy.justPressed(Arduboy::ButtonA))
	{
		this->state = ProgmemRead<StateType>(&this->options[this->selectedOption].state);
		switch(this->state)
		{
			case StateType::EditingActionList:
			{
				break;
			}
			case StateType::RunningActions:
			{
				this->nextAction = 0;
				auto selectedLevel = machine.getContext().selectedLevel;	
				this->loadLevel(selectedLevel);
				break;
			}
			case StateType::Quit:
			{
				break;
			}		
			default: break;
		}
	}
}

void GameplayState::renderOptions(StateMachine & machine)
{
	auto arduboy = machine.getContext().arduboy;
	
	const auto x = (2 * FontCharWidth);
	const auto yBase = 4;
	
	for(uint8_t i = 0; i < ArrayLength(options); ++i)
	{
		auto y = yBase + (i * FontLineHeight);
		arduboy.setCursor(x, y);
		arduboy.print(FlashString(ProgmemRead<const char *>(&options[i].text)));
		
		if(this->selectedOption == i)
			Sprites::drawOverwrite(x - (2 * FontCharWidth), y, SmallArrowImages, 1);
	}
}

//
// State::EditingActionList
//

void GameplayState::updateEditingActionList(StateMachine & machine)
{
	auto arduboy = machine.getContext().arduboy;
	
	if(arduboy.justPressed(Arduboy::ButtonUp))
	{
		if(this->selectedAction > this->actions.getFirstIndex())
			--this->selectedAction;
	}
	
	if(arduboy.justPressed(Arduboy::ButtonDown))
	{
		if(this->selectedAction < this->actions.getLastIndex())
			++this->selectedAction;
	}
	
	if(arduboy.justPressed(Arduboy::ButtonA))
	{
		this->state = StateType::EditingCurrentAction;
	}
	
	if(arduboy.justPressed(Arduboy::ButtonB))
	{
		this->state = StateType::Options;
	}
}

void GameplayState::renderEditingActionList(StateMachine & machine)
{
	auto arduboy = machine.getContext().arduboy;
	{
		// Layout constants
		const auto centreY = CalculateCentreY(ActionIconHeight);
		const auto singleMargin = 2;
		const auto doubleMargin = singleMargin * 2;
		
		const auto selectedIconHeight = ActionIconHeight + doubleMargin;
		const auto selectedIconWidth = ActionIconWidth + doubleMargin;
				
		// Draw level names, including previous two and next two
		for(int8_t i = -2; i <= +2; ++i)
		{
			const int8_t index = this->selectedAction + i; // int8_t is cheaper than integer promotion
			const size_t levelCount = ArrayLength(Levels); // Caching saves 2 bytes
			if(index >= 0 && static_cast<uint8_t>(index) < this->actions.getCount())
			{
				const auto x = ((ScreenWidth / 4) * 3) + doubleMargin;
				const auto y = centreY + (selectedIconHeight * i);
				
				auto & action = this->actions[index];
				Sprites::drawOverwrite(x, y, ActionIcons, static_cast<uint8_t>(action.getId()));
				
				arduboy.setCursor(x + selectedIconWidth, y);
				arduboy.print(index);
				
				if(action.getId() == ActionId::ForStart)
				{
					arduboy.setCursor(x + selectedIconWidth, y + FontLineHeight);
					arduboy.print(action.getArgument());				
				}
			}
		}
		
		// Draw selector
		arduboy.drawRect(((ScreenWidth / 4) * 3) + singleMargin, centreY - singleMargin, selectedIconWidth, selectedIconHeight, Arduboy::ColourWhite);
	}
	
	/*auto x = HalfScreenWidth + 4;
	auto y = 2;
	
	for(uint8_t i = 0; i < this->actions.getCount(); ++i)
	{
		auto divi = i / 7;
		auto modi = i % 7;
		
		auto drawX = x + (modi * 8);
		auto drawY = y + (divi * 8);
		
		arduboy.drawRect(drawX, drawY, 8, 8, Arduboy::ColourWhite);
		
		auto colour = (this->actions[i].getId() != ActionId::None) ? Arduboy::ColourWhite : Arduboy::ColourBlack;
		arduboy.fillRect(drawX + 2, drawY + 2, 4, 4, colour);
		
		if(i == this->selectedAction)
			arduboy.drawRect(drawX - 2, drawY - 2, 12, 12, Arduboy::ColourWhite);	
	}
	{
		constexpr const uint8_t x = CalculateCentreX(HalfScreenWidth, ScreenWidth, ActionIconWidth);
		constexpr const uint8_t y = ScreenHeight - (ActionIconHeight + 2);
		auto & action = this->actions[this->selectedAction];
		Sprites::drawOverwrite(x, y, ActionIcons, static_cast<uint8_t>(action.getId()));
		if(action.getId() == ActionId::ForStart)
		{
			arduboy.setCursor(x + ActionIconWidth + 2, y + ((ActionIconHeight - FontLineHeight) / 2));
			arduboy.print(action.getArgument());
			
			auto arrowX = this->editingArgument ? x + ActionIconWidth + 2 : x + 2;			
			Sprites::drawOverwrite(arrowX, y - SmallArrowImageHeight, SmallArrowImages, 2);
		}
	}*/
}

//
// State::EditingCurrentAction
//

void GameplayState::updateEditingCurrentAction(StateMachine & machine)
{
	auto arduboy = machine.getContext().arduboy;
	
	auto & action = this->actions[this->selectedAction];
	
	if(arduboy.justPressed(Arduboy::ButtonRight))
	{
		action.getId() = nextActionIdWrapped(action.getId());
	}
	
	if(arduboy.justPressed(Arduboy::ButtonLeft))
	{
		action.getId() = previousActionIdWrapped(action.getId());
	}
	
	if(arduboy.justPressed(Arduboy::ButtonUp))
	{
		if(action.getArgument() < 255)
			++action.getArgument();
	}
	
	if(arduboy.justPressed(Arduboy::ButtonDown))
	{
		if(action.getArgument() > 0)
			--action.getArgument();
	}
	
	if(arduboy.justPressed(Arduboy::ButtonA))
	{
		this->state = StateType::EditingActionList;
	}
}

void GameplayState::renderEditingCurrentAction(StateMachine & machine)
{
	auto arduboy = machine.getContext().arduboy;
	{
		// Layout constants
		const auto centreY = CalculateCentreY(ActionIconHeight);
		const auto singleMargin = 2;
		const auto doubleMargin = singleMargin * 2;
		
		const auto selectedIconHeight = ActionIconHeight + doubleMargin;
		const auto selectedIconWidth = ActionIconWidth + doubleMargin;
				
		// Draw level names, including previous two and next two
		for(int8_t i = -2; i <= +2; ++i)
		{
			const int8_t index = this->selectedAction + i; // int8_t is cheaper than integer promotion
			const size_t levelCount = ArrayLength(Levels); // Caching saves 2 bytes
			if(index >= 0 && static_cast<uint8_t>(index) < this->actions.getCount())
			{
				const auto x = ((ScreenWidth / 4) * 3) + doubleMargin;
				const auto y = centreY + (selectedIconHeight * i);
				
				auto & action = this->actions[index];
				Sprites::drawOverwrite(x, y, ActionIcons, static_cast<uint8_t>(action.getId()));
				
				arduboy.setCursor(x + selectedIconWidth, y);
				arduboy.print(index);
				
				if(action.getId() == ActionId::ForStart)
				{
					arduboy.setCursor(x + selectedIconWidth, y + FontLineHeight);
					arduboy.print(action.getArgument());				
				}
			}
		}
		
		// Draw selector
		arduboy.drawRect(((ScreenWidth / 4) * 3) + singleMargin, centreY - singleMargin, selectedIconWidth, selectedIconHeight, Arduboy::ColourWhite);
	}
	
	/*{	
		auto x = HalfScreenWidth + 4;
		auto y = 2;
		
		for(uint8_t i = 0; i < this->actions.getCount(); ++i)
		{
			auto divi = i / 7;
			auto modi = i % 7;
			
			auto drawX = x + (modi * 8);
			auto drawY = y + (divi * 8);
			
			arduboy.drawRect(drawX, drawY, 8, 8, Arduboy::ColourWhite);
			
			auto colour = (this->actions[i].getId() != ActionId::None) ? Arduboy::ColourWhite : Arduboy::ColourBlack;
			arduboy.fillRect(drawX + 2, drawY + 2, 4, 4, colour);
			
			if(i == this->selectedAction)
				arduboy.drawRect(drawX - 2, drawY - 2, 12, 12, Arduboy::ColourWhite);	
		}
	}
	{
		constexpr const uint8_t x = CalculateCentreX(HalfScreenWidth, ScreenWidth, ActionIconWidth);
		constexpr const uint8_t y = ScreenHeight - (ActionIconHeight + 2);
		auto & action = this->actions[this->selectedAction];
		Sprites::drawOverwrite(x, y, ActionIcons, static_cast<uint8_t>(action.getId()));
		if(action.getId() == ActionId::ForStart)
		{
			arduboy.setCursor(x + ActionIconWidth + 2, y + ((ActionIconHeight - FontLineHeight) / 2));
			arduboy.print(action.getArgument());
			
			auto arrowX = this->editingArgument ? x + ActionIconWidth + 2 : x + 2;			
			Sprites::drawOverwrite(arrowX, y - SmallArrowImageHeight, SmallArrowImages, 2);
		}
	}*/
}

//
// State::RunningActions
//

void GameplayState::updateRunningActions(StateMachine & machine)
{
	if(this->nextAction >= this->actions.getCount())
		return;

	auto arduboy = machine.getContext().arduboy;
	
	if(arduboy.justPressed(Arduboy::ButtonB))
	{
		this->state = StateType::Options;
	}

	if((arduboy.pressed(Arduboy::ButtonB) && arduboy.everyXFrames(30)) || arduboy.everyXFrames(60))
	{
		auto action = this->actions[this->nextAction];
		switch(action.getId())
		{
			case ActionId::None: break;
			case ActionId::MoveForward:
			{
				switch(this->player.direction)
				{
					case Direction::North:
					{
						if(this->player.y > 0)
						{
							auto next = this->player.y - 1;
							if(!this->tiles.getItem(this->player.x, next).isSolid())
								this->player.y = next;
						}
						break;
					}
					case Direction::East:
					{
						if(this->player.x < (this->tiles.getWidth() - 1))
						{
							auto next = this->player.x + 1;
							if(!this->tiles.getItem(next, this->player.y).isSolid())
								this->player.x = next;
						}
						break;
					}
					case Direction::South:
					{
						if(this->player.y < (this->tiles.getHeight() - 1))
						{
							auto next = this->player.y + 1;
							if(!this->tiles.getItem(this->player.x, next).isSolid())
								this->player.y = next;
						}
						break;
					}
					case Direction::West:
					{
						if(this->player.x > 0)
						{
							auto next = this->player.x - 1;
							if(!this->tiles.getItem(next, this->player.y).isSolid())
								this->player.x = next;
						}
						break;
					}
					default:
					{
						this->reportError(ErrorType::InvalidPlayerDirection);
						return;
					}
				}
				this->checkForCollectableCollision();
				if(this->collectables.isEmpty())
				{
					this->state = StateType::Success;
					return;
				}
				break;
			}
			case ActionId::TurnLeft:
			{
				--this->player.direction;
				break;
			}
			case ActionId::TurnRight:
			{
				++this->player.direction;
				break;
			}
			case ActionId::ForStart:
			{
				if(this->forStack.isFull())
				{
					// This might happen but is unlikely
					this->reportError(ErrorType::TooManyNestedForLoops);
					return;
				}

				this->forStack.push(ForLoopState(action.getArgument(), this->nextAction));
				break;
			}
			case ActionId::ForEnd:
			{
				if(this->forStack.isEmpty())
				{
					// This should never happen
					this->reportError(ErrorType::TooManyForEnds);
					return;
				}

				auto & state = this->forStack.peek();
				if(state.next())
					nextAction = state.getActionIndex();
				else
					this->forStack.drop();
				break;
			}
			default:
			{
				this->reportError(ErrorType::UnrecognisedInstruction);
				return;
			}
		}

		++this->nextAction;

		if(this->nextAction >= this->actions.getCount())
		{
			this->state = StateType::EditingActionList;
			if(!this->forStack.isEmpty())
			{
				// This should never happen
				this->reportError(ErrorType::TooManyForStarts);
				return;
			}
		}
	}
}

void GameplayState::renderRunningActions(StateMachine & machine)
{
	constexpr const uint8_t x = CalculateCentreX(HalfScreenWidth, ScreenWidth, ActionIconWidth);
	constexpr const uint8_t y = ScreenHeight - (ActionIconHeight + 2);
	if(this->nextAction > 0)
	{
		auto id = this->actions[this->nextAction - 1].getId();
		Sprites::drawOverwrite(x, y, ActionIcons, static_cast<uint8_t>(id));
	}
}

//
// Misc
//


void GameplayState::loadLevel(uint8_t selectedLevel)
{	
	if(selectedLevel >= ArrayLength(Levels))
	{
		// Panic!!
		return;
	}
	
	LevelData levelData = ProgmemRead(&Levels[selectedLevel]);

	this->actions.resize(levelData.maxActions);
	this->player = levelData.playerStart;
	TileLoader<TileGrid::Width, TileGrid::Height>::LoadProgmem(this->tiles, levelData.tileData);
	
	this->collectables.clear();
	auto count = levelData.collectableData.collectableCount;
	for(uint8_t i = 0; i < count; ++i)
	{
		this->collectables.add(ProgmemRead(&levelData.collectableData.collectables[i]));
	}
}

void GameplayState::reportError(ErrorType error)
{
	this->error = error;
	this->state = StateType::Error;
}

void GameplayState::checkForCollectableCollision(void)
{
	for(uint8_t i = this->collectables.getFirstIndex(); i < this->collectables.getCount();)
	{
		if(this->player.x == this->collectables[i].x && this->player.y == this->collectables[i].y)
		{
			this->collectables.removeAt(i);
			break;
		}
		else
		{
			++i;
		}
	}
}

//
// Misc Render
//

void GameplayState::renderGrid(StateMachine & machine)
{
	auto arduboy = machine.getContext().arduboy;

	auto offsetX = ScreenWidth / 4;
	for(uint8_t y = 0; y < TileGrid::Height; ++y)
	for(uint8_t x = 0; x < TileGrid::Width; ++x)
	{
		auto tile = tiles.getItem(x, y);
		if(tile.isSolid())
			arduboy.drawRect(offsetX + x * 8, y * 8, SmallRabbitImageWidth, SmallRabbitImageHeight, Arduboy::ColourWhite);
	}
	arduboy.drawRect(offsetX, 0, SmallRabbitImageWidth * TileGrid::Width, SmallRabbitImageHeight * TileGrid::Height, Arduboy::ColourWhite);
}

void GameplayState::renderEntity(StateMachine & machine)
{
	Sprites::drawOverwrite((ScreenWidth / 4) + player.x * 8, player.y * 8, SmallRabbitImages, static_cast<uint8_t>(player.direction));
	//Sprites::drawExternalMask(player.x * 8, player.y * 8, SmallRabbitImages, SmallRabbitMasks, static_cast<uint8_t>(player.direction), static_cast<uint8_t>(player.direction));
}

void GameplayState::renderCollectables(StateMachine & machine)
{
	for(uint8_t i = 0; i < collectables.getCount(); ++i)
	{
		Sprites::drawOverwrite((ScreenWidth / 4) + collectables[i].x * 8, collectables[i].y * 8, SmallCollectableImages, 0);
		//Sprites::drawExternalMask(collectables[i].x * 8, collectables[i].y * 8, SmallCollectableImages, SmallCollectableMasks, 0, 0);
	}
}

void GameplayState::renderPlayfield(StateMachine & machine)
{
	renderGrid(machine);
	renderCollectables(machine);
	renderEntity(machine);
}