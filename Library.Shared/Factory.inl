#include "Factory.h"

namespace FieaGameEngine
{
	template <typename T>
	void Factory<T>::Add(std::unique_ptr<const Factory> newFactory)
	{
		Factories.Insert(std::pair(newFactory.get()->ClassName(), std::move(newFactory))); //If insert finds an existing matching key, it simply returns an iterator and false bool without doing anything else.
		//Otherwise, it will insert a new value. Because of this, we don't need to do precursory check that the key doesn't already exist. We can just call insert and end it.
	}

	template <typename T>
	void Factory<T>::Remove(const std::string& targetFactory)
	{
		Factories.Remove(targetFactory);
	}

	template <typename T>
	const Factory<T>* Factory<T>::Find(const std::string& className)
	{
		if (Factories.ContainsKey(className))
		{
			return Factories.At(className).get();
		}
		return nullptr;
	}

	template <typename T>
	gsl::owner<T*> Factory<T>::Create(const std::string& className)
	{
		auto factoryType = Find(className);
		if (factoryType != nullptr)
		{
			return factoryType->Create();
		}
		return nullptr;
	}

	template <typename T>
	inline gsl::owner<T*> Factory<T>::Create() const
	{
	}

	template <typename T>
	const std::string& Factory<T>::ClassName() const
	{
	}
}