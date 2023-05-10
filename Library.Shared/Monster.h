#pragma once
#include "Scope.h"
#include "Vector.h"
#include "Attributed.h"
#include "Factory.h"

namespace UnitTests
{
	class Monster : public FieaGameEngine::Attributed
	{
		RTTI_DECLARATIONS(Monster, FieaGameEngine::Attributed);

	public:
		static const std::size_t ArraySize = 3;

		Monster();
		Monster(const Monster&) = default;
		Monster(Monster&&) = default;
		Monster& operator=(const Monster&) = default;
		Monster& operator=(Monster&&) = default;
		~Monster() = default;

		float Attack = 0.0f;
		float Defense = 0.0f;
		float Health = 0.0f;
		size_t Victims = 0;
		std::string Name = "";

		static FieaGameEngine::Vector<FieaGameEngine::Signature> Signatures();
	};
	ConcreteFactory(Monster, FieaGameEngine::Scope);
}