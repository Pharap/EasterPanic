#pragma once

namespace Details
{
	template< typename T, T ... Ts>
	struct MaxValueHelper;

	template< typename T, T A>
	struct MaxValueHelper<T, A>
	{
		constexpr const static T Value = A;
	};

	template< typename T, T A, T B>
	struct MaxValueHelper<T, A, B> : MaxValueHelper<T, (A > B) ? A : B>
	{
	};

	template< typename T, T A, T B, T ... Ts>
	struct MaxValueHelper<T, A, B, Ts...> : MaxValueHelper<T, MaxValueHelper<T, A, B>::Value, Ts...>
	{
	};
}

template< typename T, T ... Ts >
constexpr T MaxValue(void)
{
	return Details::MaxValueHelper<T, Ts ...>::Value;
}

namespace Details
{
	template< typename T, T ... Ts>
	struct MinValueHelper;

	template< typename T, T A>
	struct MinValueHelper<T, A>
	{
		constexpr const static T Value = A;
	};

	template< typename T, T A, T B>
	struct MinValueHelper<T, A, B> : MinValueHelper<T, (A < B) ? A : B>
	{
	};

	template< typename T, T A, T B, T ... Ts>
	struct MinValueHelper<T, A, B, Ts...> : MinValueHelper<T, MinValueHelper<T, A, B>::Value, Ts...>
	{
	};
}

template< typename T, T ... Ts >
constexpr T MinValue(void)
{
	return Details::MinValueHelper<T, Ts ...>::Value;
}