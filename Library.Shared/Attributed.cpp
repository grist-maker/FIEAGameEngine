#include "Attributed.h"

/// <summary>
/// Method definitions to support the Attributed class. 
/// </summary>
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Attributed);
	Attributed::Attributed(RTTI::IdType typeId)
	{
		Populate(typeId);
	}

	Attributed::Attributed(const Attributed& copiedAttributed):
		Scope(copiedAttributed)
	{
		SetExternalStorage(copiedAttributed.TypeIdInstance());
	}

	Attributed::Attributed(Attributed&& movedAttributed) noexcept
		: Scope(std::move(movedAttributed))
	{
		SetExternalStorage(movedAttributed.TypeIdInstance());
	}

	Attributed& Attributed::operator=(const Attributed& copiedAttributed)
	{
		if (this != &copiedAttributed)
		{
			Scope::operator=(copiedAttributed);
			SetExternalStorage(copiedAttributed.TypeIdInstance());
		}
		return *this;
	}

	Attributed& Attributed::operator=(Attributed&& movedAttributed) noexcept
	{
		if (this != &movedAttributed)
		{
			Scope::operator=(std::move(movedAttributed));
			SetExternalStorage(movedAttributed.TypeIdInstance());
		}
		return *this;
	}

	void Attributed::SetExternalStorage(RTTI::IdType typeId)
	{
		const Vector<Signature>& signatures = TypeManager::Instance()->GetSignatures(typeId);
		auto& thisRef = Append("this");
		thisRef.SetType(Datum::DatumTypes::Pointer);
		thisRef.SetRTTI(static_cast<RTTI*>(this));
		for (size_t i = 0; i < signatures.Size(); i++)
		{
			auto& currentSignature = signatures[i];
			if(currentSignature.Type != Datum::DatumTypes::Table)
			{
				auto& currentDatum = Scope::At(i+1);
				void* storage = reinterpret_cast<std::byte*>(this) + currentSignature.Offset;
				currentDatum.SetStorage(currentSignature.Type, storage, currentSignature.Size);
			}
		}

	}

	Datum* Attributed::At(const std::string& key) const
	{
		return (Scope::Find(key));
	}

	Datum& Attributed::At(size_t index) const
	{
		return (*At(OrderTable[index]->first));
	}

	size_t Attributed::Size() const
	{
		return(Scope::Size());
	}

	void Attributed::Populate(RTTI::IdType typeId)
	{
		const Vector<Signature>& signatures = TypeManager::Instance()->GetSignatures(typeId);
		auto& thisRef = Append("this");
		thisRef.SetType(Datum::DatumTypes::Pointer);
		thisRef.PushBack(static_cast<RTTI*>(this));

		for (size_t i = 0; i < signatures.Size(); i++)
		{
			auto& currentSignature = signatures[i];
			if (currentSignature.Type == Datum::DatumTypes::Table)
			{
				AppendScope(currentSignature.Name);
				Scope::operator[](i + 1).Reserve(currentSignature.Size);
			}
			else
			{
				Datum& currentDatum = Append(currentSignature.Name);
				void* storage = reinterpret_cast<std::byte*>(this) + currentSignature.Offset;
				currentDatum.SetStorage(currentSignature.Type,  storage, currentSignature.Size);
			}
		}
	}

	bool Attributed::IsAttribute(const std::string& name) const
	{
		return Find(name) != nullptr;
	}

	bool Attributed::IsPrescribedAttribute(const std::string& name) const
	{
		if (IsAttribute(name))
		{
			for (size_t i = 1; i < TypeManager::Instance()->GetSignatures(TypeIdInstance()).Size() + 1; i++)
			{
				if (OrderTable[i]->first == name)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool Attributed::IsAuxiliaryAttribute(const std::string& name) const
	{
		if (IsAttribute(name) && !IsPrescribedAttribute(name))
		{
			return true;
		}
		return false;
	}

	Datum& Attributed::AppendAuxiliaryAttribute(const std::string& name)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::runtime_error("Cannot add auxiliary attribute that uses key associated with prescribed attribute!");
		}
		return Append(name);
	}

	std::pair<size_t, size_t> Attributed::GetAttributes() const
	{
		return std::pair(1, OrderTable.Size());
	}

	std::pair<size_t, size_t> Attributed::GetPrescribedAttributes() const
	{
		return std::pair(1, TypeManager::Instance()->GetSignatures(TypeIdInstance()).Size() + 1);
	}

	std::pair<size_t, size_t> Attributed::GetAuxiliaryAttributes() const
	{
		return std::pair(TypeManager::Instance()->GetSignatures(TypeIdInstance()).Size() + 1, OrderTable.Size());
	}
}