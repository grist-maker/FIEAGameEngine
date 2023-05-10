#pragma once
#include <cstdint>
#include <string.h>
/// <summary>
/// Defines the default equality functors to be used to establish equality between different kinds of values. Used to support HashMap.
/// </summary>
namespace FieaGameEngine
{
	template <typename T>
	struct DefaultEquality final
	{
		template <typename T>
		inline bool operator()(const T& lhs, const T& rhs) const
		{
			return lhs == rhs;
		}

	};

	template<>
	struct DefaultEquality<char*> final
	{
		inline bool operator()(const char* lhs, const char* rhs) const
		{
			return strcmp(lhs, rhs) == 0;
		}
	};

	template<>
	struct DefaultEquality<const char*> final
	{
		inline bool operator()(const char* lhs, const char* rhs) const
		{
			return strcmp(lhs, rhs) == 0;
		}
	};

	template<>
	struct DefaultEquality<char* const> final
	{
		inline bool operator()(const char* const lhs, const char* const rhs) const
		{
			return strcmp(lhs, rhs) == 0;
		}
	};

	template<>
	struct DefaultEquality<const char* const> final
	{
		inline bool operator()(const char* const lhs, const char* const rhs) const
		{
			return strcmp(lhs, rhs) == 0;
		}
	};
}