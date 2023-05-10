#include "EventMessageAttributed.h"
#include "pch.h"
using namespace std;
using namespace std::string_literals;
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventMessageAttributed);
	
	EventMessageAttributed::EventMessageAttributed(std::string subtype) :
		Attributed(TypeIdClass())
	{
		SetSubtype(subtype);
	}

	EventMessageAttributed::EventMessageAttributed(size_t typeId) :
		Attributed(typeId)
	{
	}

	Vector<Signature> EventMessageAttributed::Signatures()
	{
		Vector<Signature> signatureArray;
		signatureArray.PushBack(Signature{ "Subtype", Datum::DatumTypes::String, 1, offsetof(EventMessageAttributed, Subtype) });
		return signatureArray;
	}

	const std::string& EventMessageAttributed::GetSubtype() const
	{
		return Subtype;
	}

	void EventMessageAttributed::SetSubtype(std::string newName)
	{
		Subtype = newName;
	}
}