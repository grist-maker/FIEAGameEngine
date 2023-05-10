#pragma once
#include <cstdio>
#include <string>
#include <vector>
//#include "CppUnitTest.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Class that defines all hash functions to be used alongside the HashMap. Contains a default T function, as well as specializations for std::string and char*.
	/// </summary>
	template <typename T>
	struct HashFunctor final
	{
		size_t operator()(const T& key) const
		{
			const std::byte* data = reinterpret_cast<const std::byte*>(&key);

			auto size = sizeof(T);
			size_t hashValue = 0;
			const auto hashPrime = 31;

			for (std::size_t index = 0; index <size; ++index)
			{
				hashValue += static_cast<size_t>(data[index]) * hashPrime; //Number is parsed, byte by byte, to get the value.
			}
			return hashValue;
		}
	};
	template <>
	struct HashFunctor<char*> final
	{
		size_t operator()(const char* key) const
		{
			size_t hashValue = 0;
			for (size_t counter = 0; key[counter] != '\0'; counter++)
			{
				//This produces a unique hash for each possible string value. The byte value of each character is converted to a size_t.
				//This size_t is multiplied by 100^counter, ensuring that the strings "ah" and "ha" would not be considered equal. 
				hashValue += static_cast<size_t>(pow(100, static_cast<double>(counter))) * static_cast<size_t>(std::byte(key[counter]));//static_cast<size_t> (pow(100, counter)) * static_cast<size_t>(std::byte(key[counter]));
			}
			return hashValue;
		}
	};

	template <>
	struct HashFunctor<const char*> final
	{
		size_t operator()(const char* key) const
		{
			size_t hashValue = 0;
			for (size_t counter = 0; key[counter] != '\0'; counter++)
			{
				//This produces a unique hash for each possible string value. The byte value of each character is converted to a size_t.
				//This size_t is multiplied by 100^counter, ensuring that the strings "ah" and "ha" would not be considered equal. 
				hashValue += static_cast<size_t> (pow(100, static_cast<double>(counter))) * static_cast<size_t>(std::byte(key[counter]));
			}
			return hashValue;
		}
	};

	template <>
	struct HashFunctor<std::string> final
	{
		size_t operator()(const std::string& key)
		{
			size_t hashValue = 0;
			
			for (size_t counter = 0; counter < key.size(); counter++)
			{
				//This produces a unique hash for each possible string value. The byte value of each character is converted to a size_t.
				//This size_t is multiplied by 100^counter, ensuring that the strings "ah" and "ha" would not be considered equal. 
				hashValue +=static_cast<size_t> (pow(100, static_cast<double>(counter))) * static_cast<size_t>(std::byte(key[counter]));
			}
			return hashValue;
		}
	};

	template <>
	struct HashFunctor<const std::string> final
	{
		size_t operator()(const std::string& key)
		{
			size_t hashValue = 0;

			for (size_t counter = 0; counter < key.size(); counter++)
			{
				//This produces a unique hash for each possible string value. The byte value of each character is converted to a size_t.
				//This size_t is multiplied by 100^counter, ensuring that the strings "ah" and "ha" would not be considered equal. 
				hashValue += static_cast<size_t> (pow(100, static_cast<double>(counter))) * static_cast<size_t>(std::byte(key[counter]));
			}
			return hashValue;
		}
	};
}