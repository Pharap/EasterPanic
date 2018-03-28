#pragma once

#include "Arduboy2PrettificationUtils.h"

constexpr const static uint8_t ScreenWidth = Arduboy::ScreenWidth;
constexpr const static uint8_t ScreenHeight = Arduboy::ScreenHeight;
constexpr const static uint8_t HalfScreenWidth = (ScreenWidth / 2);
constexpr const static uint8_t HalfScreenHeight = (ScreenHeight / 2);

constexpr int16_t CalculateCentreX(const uint8_t & width)
{
	return HalfScreenWidth - static_cast<int16_t>(round(width / 2.0));
}

constexpr int16_t CalculateCentreY(const uint8_t & height)
{
	return HalfScreenHeight - static_cast<int16_t>(round(height / 2.0));
}

constexpr int16_t CalculateCentre(const uint8_t & maxDimension, const uint8_t & dimension)
{
	return static_cast<int16_t>(round(maxDimension / 2.0)) - static_cast<int16_t>(round(dimension / 2.0));
}

constexpr int16_t CalculateCentreX(const uint8_t & x, const uint8_t & maxWidth, const uint8_t & width)
{
	return (x + ((maxWidth - x) / 2)) - static_cast<int16_t>(round(width / 2.0));
}

constexpr int16_t CalculateCentreY(const uint8_t & y, const uint8_t & maxHeight, const uint8_t & height)
{
	return (y + ((maxHeight - y) / 2)) - static_cast<int16_t>(round(height / 2.0));
}