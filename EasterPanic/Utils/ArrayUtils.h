#pragma once

//
// ArrayLength
//

template< typename T, size_t Size >
constexpr size_t ArrayLength(T (&)[Size])
{
	return Size;
}

template< typename T >
constexpr size_t ArrayLength(T(&)[0])
{
	return 0;
}

//
// StringLength
//

template< typename T, size_t Size >
constexpr size_t StringLength(T (&)[Size])
{
	return Size - 1;
}