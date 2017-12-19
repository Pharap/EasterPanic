#pragma once

#include "ArrayUtils.h"
#include <avr/pgmspace.h>

constexpr const static uint8_t FontCharWidth = 5;
constexpr const static uint8_t FontCharHeight = 7;
constexpr const static uint8_t FontSpaceWidth = 1;
constexpr const static uint8_t FontSpaceHeight = 1;
constexpr const static uint8_t FontLineHeight = FontCharHeight + FontSpaceHeight;

template< typename T, size_t N > constexpr size_t StringWidth(T (&string)[N])
{
	return (StringLength(string) * FontCharWidth) + ((StringLength(string) - 1) * FontSpaceWidth);
}

constexpr uint8_t StringHeight(uint8_t lineCount)
{
	return (lineCount * FontCharHeight) + ((lineCount - 1) * FontSpaceHeight);
}

inline size_t RuntimeStringWidth(const char * string)
{
	auto length = strlen(string);
	return (length * (FontCharWidth)) + ((length - 1) * FontSpaceWidth);
}

inline size_t ProgmemStringWidth(const char * string)
{
	auto length = strlen_P(string);
	return (length * (FontCharWidth)) + ((length - 1) * FontSpaceWidth);
}