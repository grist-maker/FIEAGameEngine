#include "Scope.h"
#include "Attributed.h"

/// <summary>
/// Method definitions to support the Scope class.
/// </summary>
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Scope);

	Scope::Scope(size_t capacity)
	{
		OrderTable.Reserve(capacity);
	}

	Scope::~Scope()
	{
		Clear();
	}

	Scope::Scope(const Scope& other)
	{
		DeepCopy(other);
	}

	Scope::Scope(Scope&& movedScope) noexcept
		: OrderTable(std::move(movedScope.OrderTable))
		 ,ScopeData(std::move(movedScope.ScopeData))
	{
		if (movedScope.Parent != nullptr)
		{
			movedScope = *movedScope.Orphan();
			delete(&movedScope);
		}
	}

	Scope& Scope::operator=(Scope&& movedScope) noexcept
	{
		if (movedScope != *this)
		{
			Clear();
			OrderTable = std::move(movedScope.OrderTable);
			ScopeData = std::move(movedScope.ScopeData);
			if (movedScope.Parent != nullptr)
			{
				movedScope = *movedScope.Orphan();
				delete(&movedScope);
			}
			if (Parent != nullptr)
			{
				delete(Orphan());
			}
		}
		return *this;
	}

	Scope& Scope::operator=(const Scope& other)
	{
		if (this != &other)
		{
			Clear();
			OrderTable.Reserve(other.OrderTable.Size());
			DeepCopy(other);
		}
		return *this;
	}

	Datum& Scope::operator[](const std::string& datumName)
	{
		return Append(datumName);
	}

	Datum& Scope::operator[](size_t datumIndex)
	{
		return (At(datumIndex));
	}

	bool Scope::operator==(const Scope& comparedScope) const
	{
		if (ScopeData.Size() != comparedScope.ScopeData.Size())
		{
			return false;
		}
		size_t i = 0;
		if (comparedScope.Is(Attributed::TypeIdClass()))
		{
			i = 1;
		}
		for (i; i < OrderTable.Size(); i++)
		{
			Datum* currentValue = Find(comparedScope.OrderTable[i]->first);

			if (currentValue == nullptr || currentValue->Type() != comparedScope.OrderTable[i]->second.Type())
			{
				return false;
			}

			if (currentValue->Type() == Datum::DatumTypes::Table && *(currentValue->GetScope()) != *(comparedScope.OrderTable[i]->second.GetScope()))
			{
				return false;
			}

			else if (currentValue->Type() != Datum::DatumTypes::Table && *currentValue != comparedScope.OrderTable[i]->second)
			{
				return false;
			}
		}
		return true;
	}

	bool Scope::operator!=(const Scope& comparedScope) const
	{
		return !(*this == comparedScope);
	}

	Datum* Scope::Find(const std::string& key) const
	{
		size_t i = 0;
		for (i = 0; i < OrderTable.Size(); i++)
		{
			if(OrderTable[i]->first == key)
			{
				break;
			}
		}
		if (i >= OrderTable.Size())
		{
			return nullptr;
		}
		return (&OrderTable[i]->second);
	}

	Datum* Scope::Search(const std::string& key, Scope*& foundScope)
	{
		Datum* locatedValue = Find(key);
		if (locatedValue == nullptr)
		{
			if (Parent != nullptr)
			{
				return(Parent->Search(key, foundScope));
			}
			foundScope = nullptr;
		}
		else
		{
			foundScope = this;
		}
		return locatedValue;
	}

	Datum* Scope::Search(const std::string& key) const
	{
		Datum* locatedValue = Find(key);
		if (locatedValue == nullptr)
		{
			if (Parent != nullptr)
			{
				return(Parent->Search(key));
			}
		}
		return locatedValue;
	}

	Datum& Scope::At(size_t index) const //This returns the targeted scope.
	{
		return (OrderTable[index]->second);
	}

	Datum& Scope::Append(const std::string& datumName)
	{
		auto result = ScopeData.Insert(std::pair(datumName, Datum()));
		if (result.second)
		{
			OrderTable.PushBack(&(*result.first));
		}
		return (*result.first).second;
	}

	Scope& Scope::AppendScope(const std::string& name)
	{
		auto& foundDatum = Append(name);
		if (foundDatum.Type() != Datum::DatumTypes::Table && foundDatum.Type() != Datum::DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot add Scope when existing key is tied to a non-scope object!");
		}
		else if(foundDatum.Type() != Datum::DatumTypes::Table)
		{
			Scope* data = new Scope;
			Adopt(data, name); //Adopts new scope child
			return (*this);
		}
		Adopt(foundDatum.GetScope(), name);
		return(*this);
	}

	[[nodiscard]] void Scope::Adopt(Scope* child, const std::string & childKey)
	{
		if (child == nullptr)
		{
			return;
		}
		if (child->Parent == this)
		{ 
			return;
		}
		if (IsDescendantOf(*child) || this == child)
		{
			throw std::runtime_error("Cannot adopt an acestor or yourself!");
		}
		Datum& datum = Append(childKey);
		if (datum.Type() != Datum::DatumTypes::Unknown && datum.Type() != Datum::DatumTypes::Table)
		{ 
			throw std::runtime_error("The specified ley already exists but is not of type Scope."); 
		}
		// All validation is complete and we should be guaranteed that this operation will succeed.     
		child->Orphan();
		child->Parent = this;
		datum.PushBack(child);
	}

	Scope* Scope::Orphan()
	{
		if (Parent != nullptr)
		{
			auto [datum, datumIndex] = Parent->FindContainedScope(this); //We find the object containing it to orphan the scope.
			assert(datum != nullptr);
			datum->RemoveAt(datumIndex);
			Parent = nullptr;
			return this;
		}
		return nullptr;
	}

	Scope* Scope::GetParent() const
	{
		return Parent;
	}

	std::pair<Datum*, size_t> Scope::FindContainedScope(const Scope* targetScope) const
	{
		std::pair<Datum*, size_t> newPair(nullptr, 0);
		for (size_t i = 0; i < OrderTable.Size(); i++)
		{
			if (OrderTable[i]->second.Type() == Datum::DatumTypes::Table)
			{
				for (size_t j = 0; j < OrderTable[i]->second.Size(); j++)
				{
					if (OrderTable[i]->second.GetScope(j) == targetScope)
					{
						newPair.first = &OrderTable[i]->second;
						newPair.second = j;
						break;
					}
				}
			}
		}
		return newPair;
	}

	void Scope::DeepCopy(const Scope& other)
	{
		for (size_t i = 0; i < other.OrderTable.Size(); i++)
		{
			auto& targetValue = other.OrderTable[i];//[key, existingDatum] = other.OrderTable[i];
			auto& key = targetValue->first;
			auto& existingDatum = targetValue->second;

			Datum& newDatum = Append(key);

			if (existingDatum.Type() == Datum::DatumTypes::Table)
			{
				newDatum.SetType(Datum::DatumTypes::Table);
				newDatum.Reserve(existingDatum.Size());
				for (size_t j = 0; j < existingDatum.Size(); ++j)
				{
					Scope* nestedScope = existingDatum.GetScope(j)->Clone();
					nestedScope->Parent = this;
					newDatum.PushBack(nestedScope);
				}
			}
			else
			{
				newDatum = existingDatum;
			}
		}
	}

	void Scope::Clear()
	{

		for (size_t i=0; i < OrderTable.Size(); i++)
		{
			Datum& datum = OrderTable[i]->second;

			if (datum.Type() == Datum::DatumTypes::Table) // Traverse nested scopes by recursively comparing the two scopes.
			{
				for (size_t j = 0; j < datum.Size(); j++)
				{
					delete& datum[j];
				}
			}
		}
		OrderTable.Clear();
		ScopeData.Clear();
	}

	size_t Scope::Size() const
	{
		return OrderTable.Size();
	}

	Scope* Scope::Clone() const
	{
		return new Scope(*this);
	}

	const std::pair<std::string, const Datum> Scope::GetPair(size_t index) const
	{
		return (*OrderTable[index]);
	}

	bool Scope::IsDescendantOf(const Scope& targetScope) const
	{
		Scope* currentParent = Parent;
		while (currentParent != nullptr)
		{
			if (currentParent == &targetScope)
			{
				return true;
			}
			currentParent = currentParent->Parent;
		}
		return false;
	}
};