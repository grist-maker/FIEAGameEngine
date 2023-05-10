#include "pch.h"
#include "Monster.h"

using namespace std;
using namespace std::string_literals;

namespace UnitTests
{
	RTTI_DEFINITIONS(Monster);

	Monster::Monster() :
		Attributed(TypeIdClass())
	{
	}

	FieaGameEngine::Vector<FieaGameEngine::Signature> Monster::Signatures()
	{
		FieaGameEngine::Vector<FieaGameEngine::Signature> signatureArray;
		signatureArray.PushBack(FieaGameEngine::Signature{ "Attack", FieaGameEngine::Datum::DatumTypes::Float, 1, offsetof(Monster, Attack) });
		signatureArray.PushBack(FieaGameEngine::Signature{ "Defense", FieaGameEngine::Datum::DatumTypes::Float, 1, offsetof(Monster, Defense) });
		signatureArray.PushBack(FieaGameEngine::Signature{ "Health", FieaGameEngine::Datum::DatumTypes::Float, 1, offsetof(Monster, Health)});
		signatureArray.PushBack(FieaGameEngine::Signature{ "Victims", FieaGameEngine::Datum::DatumTypes::Integer, 1, offsetof(Monster, Health) });
		signatureArray.PushBack(FieaGameEngine::Signature{ "Name", FieaGameEngine::Datum::DatumTypes::String, 1, offsetof(Monster, Name) });

		return signatureArray;
	}
}
