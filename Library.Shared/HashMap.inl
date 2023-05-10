#include "HashMap.h"
/// <summary>
/// The file specifying the HashMap template functions, which is used to create HashMaps that store key value pairs, composed of Vector and SList data types. Includes definition for HashMaps of a user-defined type and iterators.
/// Includes functions to wipe, initialize, and copy HashMaps. Allows users to add new values to the HashMap, as well as iterate through and insert or remove elements between values. Additionally, includes capability to uniquely
/// hash TKey values to convert to numbers, which may then be used to further organize the hashmap and reduce time overhead in data lookups.
/// </summary>

//using namespace std::pmr;
namespace FieaGameEngine
{	
	template <typename TKey, typename TData, typename Hash>
	inline HashMap<TKey, TData, Hash>::Iterator::Iterator()
	{
 	}

	template <typename TKey, typename TData, typename Hash>
	inline HashMap<TKey, TData, Hash>::Iterator::~Iterator()
	{
		Container = 0;
		Owner = nullptr;
		typename ChainType::Iterator defaultIterator;
		Index = defaultIterator;
	}

	template <typename TKey, typename TData, typename Hash>
	inline HashMap<TKey, TData, Hash>::ConstIterator::ConstIterator()
	{
	}

	template <typename TKey, typename TData, typename Hash>
	HashMap<TKey, TData, Hash>::ConstIterator::~ConstIterator()
	{
		Container = 0;
		Owner = nullptr;
		typename ChainType::ConstIterator defaultIterator;
		Index = defaultIterator;
	}

	template <typename TKey, typename TData, typename Hash>
	inline HashMap<TKey, TData, Hash>::Iterator::Iterator(size_t container, typename SList<PairType>::Iterator index, HashMap<TKey, TData, Hash>* owner):
		Container(container), Index(index), Owner(owner)
	{
	}

	template <typename TKey, typename TData, typename Hash>
	inline HashMap<TKey, TData, Hash>::ConstIterator::ConstIterator(size_t container, typename SList<PairType>::ConstIterator index, const HashMap<TKey, TData, Hash>* owner) :
		Container(container), Index(index), Owner(owner)
	{
	}

	template <typename TKey, typename TData, typename Hash>
	HashMap<TKey, TData, Hash>::Iterator::Iterator(const Iterator& copiedIterator):
		Container(copiedIterator.Container), Index(copiedIterator.Index), Owner(copiedIterator.Owner)
	{
	}

	template <typename TKey, typename TData, typename Hash>
	HashMap<TKey, TData, Hash>::ConstIterator::ConstIterator(const ConstIterator& copiedIterator) :
		Container(copiedIterator.Container), Index(copiedIterator.Index), Owner(copiedIterator.Owner)
	{
	}

	template <typename TKey, typename TData, typename Hash>
	HashMap<TKey, TData, Hash>& HashMap<TKey, TData, Hash>::operator=(HashMap&& movedHashmap) noexcept
	{
		StoredData.Clear();
		Population = 0;

		StoredData = std::move(movedHashmap.StoredData);
		Population = movedHashmap.Population;

		movedHashmap.Clear();
		movedHashmap.Population = 0;
		return *this;
	}

	template <typename TKey, typename TData, typename Hash>
	typename HashMap<TKey, TData, Hash>::Iterator& HashMap<TKey, TData, Hash>::Iterator::operator++()
	{
		if (Owner == nullptr)
		{
			throw std::runtime_error("Iterator value is nullptr! Can not dereference.");
		}
		bool found = false;
		bool searching = true;
		while (searching && !found)
		{
			if (Container < Owner->StoredData.Size() && Index != Owner->StoredData.At(Container).end()) //Increment to the next value in the inner SList.
			{
				Index++;
			}
			else if (Container == Owner->StoredData.Size())
			{
				searching = false;
			}
			else if (Container < Owner->StoredData.Size()) //Change to next vector index otherwise.
			{
				while (Container < Owner->StoredData.Size() && Index == Owner->StoredData.At(Container).end())
				{
					Container++;
					if (Container < Owner->StoredData.Size())
					{
						Index = Owner->StoredData.At(Container).begin();
					}
				}
			}
			if ( searching && Container < Owner->StoredData.Size() && Index != Owner->StoredData.At(Container).end())
			{
				searching = false;
				found = true;
			}
		}
		if (!found)
		{
			*this = (*Owner).end();
		}
		return *this;
	}

	template <typename TKey, typename TData, typename Hash>
	typename inline HashMap<TKey, TData, Hash>::Iterator HashMap<TKey, TData, Hash>::Iterator::operator++(int)
	{
		Iterator iterator = *this;
		operator++();
		return iterator;
	}

	template <typename TKey, typename TData, typename Hash>
	typename const HashMap<TKey, TData, Hash>::ConstIterator& HashMap<TKey, TData, Hash>::ConstIterator::operator++()
	{
		if (Owner == nullptr)
		{
			throw std::runtime_error("Iterator value is nullptr! Can not dereference.");
		}
		bool found = false;
		bool searching = true;
		while (searching && !found)
		{
			if (Container < Owner->StoredData.Size() && Index != Owner->StoredData.At(Container).end()) //Increment to the next value in the inner SList.
			{
				Index++;
			}
			else if (Container == Owner->StoredData.Size())
			{
				searching = false;
			}
			else if (Container < Owner->StoredData.Size()) //Change to next vector index otherwise.
			{
				while ( Container < Owner->StoredData.Size() && Index == Owner->StoredData.At(Container).end())
				{
					Container++;
					if (Container < Owner->StoredData.Size())
					{
						Index = Owner->StoredData.At(Container).begin();
					}
				}
			}
			if (searching && Container < Owner->StoredData.Size() && Index != Owner->StoredData.At(Container).end())
			{
				searching = false;
				found = true;
			}
		}
		if (!found)
		{
			*this = (*Owner).cend();
		}
		return *this;
	}

	template <typename TKey, typename TData, typename Hash>
	typename inline HashMap<TKey, TData, Hash>::ConstIterator HashMap<TKey, TData, Hash>::ConstIterator::operator++(int)
	{
		ConstIterator iterator = *this;
		operator++();
		return iterator;
	}

	template <typename TKey, typename TData, typename Hash>
	typename void HashMap<TKey, TData, Hash>::Iterator::operator=(const HashMap<TKey, TData, Hash>::Iterator& copiedIterator)
	{
		Owner = copiedIterator.Owner;
		Index = copiedIterator.Index;
		Container = copiedIterator.Container;
	}

	template <typename TKey, typename TData, typename Hash>
	typename void HashMap<TKey, TData, Hash>::ConstIterator::operator=(const HashMap<TKey, TData, Hash>::ConstIterator& copiedIterator)
	{
		Owner = copiedIterator.Owner;
		Index = copiedIterator.Index;
		Container = copiedIterator.Container;
	}

	template <typename TKey, typename TData, typename Hash>
	typename std::pair<const TKey, TData>& HashMap<TKey, TData, Hash>::Iterator::operator*() const
	{
		if (Owner == nullptr)
		{
			throw std::runtime_error("Owner value is nullptr! Can not dereference.");
		}
		if (&Owner->StoredData == nullptr || Index == Owner->StoredData.At(Container).end())
		{
			throw std::runtime_error("Iterator value is nullptr! Can not dereference.");
		}
		return (*Index);
	}

	template <typename TKey, typename TData, typename Hash>
	typename const std::pair<const TKey, TData>& HashMap<TKey, TData, Hash>::ConstIterator::operator*() const
	{
		if (Owner == nullptr)
		{
			throw std::runtime_error("Owner value is nullptr! Can not dereference.");
		}
		if (&Owner->StoredData == nullptr || Index == Owner->StoredData.At(Container).end())
		{
			throw std::runtime_error("Iterator value is nullptr! Can not dereference.");
		}
		return ((*Index));
	}

	template <typename TKey, typename TData, typename Hash>
	typename std::pair<const TKey, TData> HashMap<TKey, TData, Hash>::Iterator::operator->() const
	{
		if (Owner == nullptr)
		{
			throw std::runtime_error("Owner value is nullptr! Can not dereference.");
		}
		if (&Owner->StoredData == nullptr || Index == Owner->StoredData.At(Container).end())
		{
			throw std::runtime_error("Iterator value is nullptr! Can not dereference.");
		}
		return (*Index);
	}

	template <typename TKey, typename TData, typename Hash>
	typename const std::pair<const TKey, TData>& HashMap<TKey, TData, Hash>::ConstIterator::operator->() const
	{
		if (Owner == nullptr)
		{
			throw std::runtime_error("Owner value is nullptr! Can not dereference.");
		}
		if (&Owner->StoredData == nullptr || Index == Owner->StoredData.At(Container).end())
		{
			throw std::runtime_error("Iterator value is nullptr! Can not dereference.");
		}
		return (*Index);
	}

	template <typename TKey, typename TData, typename Hash>
	typename bool HashMap<TKey, TData, Hash>::Iterator::operator==(HashMap<TKey, TData, Hash>::Iterator comparedIterator) const
	{
		return(Owner == comparedIterator.Owner && Index == comparedIterator.Index && Container == comparedIterator.Container);
	}

	template <typename TKey, typename TData, typename Hash>
	typename bool HashMap<TKey, TData, Hash>::Iterator::operator!=(HashMap<TKey, TData, Hash>::Iterator comparedIterator) const
	{
		return(!(Owner == comparedIterator.Owner && Index == comparedIterator.Index && Container == comparedIterator.Container));
	}

	template <typename TKey, typename TData, typename Hash>
	typename bool HashMap<TKey, TData, Hash>::ConstIterator::operator==(HashMap<TKey, TData, Hash>::ConstIterator comparedIterator) const
	{
		return(Owner == comparedIterator.Owner && Index == comparedIterator.Index && Container == comparedIterator.Container);
	}

	template <typename TKey, typename TData, typename Hash>
	typename bool HashMap<TKey, TData, Hash>::ConstIterator::operator!=(HashMap<TKey, TData, Hash>::ConstIterator comparedIterator) const
	{
		return(!(Owner == comparedIterator.Owner && Index == comparedIterator.Index && Container == comparedIterator.Container));
	}

	template <typename TKey,typename TData, typename Hash>
	HashMap<TKey, TData, Hash>::HashMap(size_t size)
	{
		if (size <= 1)
		{
			throw std::runtime_error("HashMap must have at least 2 sections!");
		}
		StoredData.Reserve(size);

		for (size_t i = 0; i < size; i++)
		{
			StoredData.PushBack(ChainType{}); //Pushing all necessary SLists into the new vector.
		}
	}

	template <typename TKey, typename TData, typename Hash>
	HashMap<TKey, TData, Hash>::~HashMap()
	{
		Clear();
	}

	template <typename TKey, typename TData, typename Hash>
	typename TData& HashMap<TKey, TData, Hash>::operator[](const TKey targetKey)
	{
		TData defaultValue;
		PairType referencedValue(targetKey, defaultValue);
		Iterator newValue = Insert(referencedValue).first;
		return (*(newValue.Index)).second;
	}

	template <typename TKey, typename TData, typename Hash>
	typename HashMap<TKey, TData, Hash>::Iterator HashMap<TKey, TData, Hash>::Find(const TKey& key, EqualityFunctor equalityFunctor)
	{
		Hash hashFunctor{};
		size_t hashedKey = hashFunctor(key);
		hashedKey %= StoredData.Size();
		Iterator traverser(hashedKey, StoredData.At(hashedKey).begin(), this);
		//Ensure hashedKey is ALWAYS equal to desired index
		for(traverser; traverser.Index != StoredData.At(hashedKey).end(); traverser++)
		{
			if (traverser.Container != hashedKey)
			{
				traverser.Index = StoredData.At(hashedKey).end();
				traverser.Container = hashedKey;
				break;
			}

			if(equalityFunctor(key, (*(traverser.Index)).first))
			{
				break;
			}
		}
		return traverser;
	}

	template <typename TKey, typename TData, typename Hash>
	typename HashMap<TKey, TData, Hash>::ConstIterator HashMap<TKey, TData, Hash>::Find(const TKey& key, EqualityFunctor equalityFunctor) const
	{
		Hash hashFunctor{};
		size_t hashedKey = hashFunctor(key);
		hashedKey %= StoredData.Size();
		ConstIterator traverser((hashedKey), StoredData.At(hashedKey).CBegin(), this);

		for (traverser; traverser.Index != StoredData.At(hashedKey).CEnd(); traverser++)
		{
			if (equalityFunctor(key, (* (traverser.Index)).first))
			{
				break;
			}
		}
		return traverser;
	}

	template <typename TKey, typename TData, typename Hash>
	std::pair<typename HashMap<TKey, TData, Hash>::Iterator, bool> HashMap<TKey, TData, Hash>::Insert(const PairType& entry)
	{
		Iterator traverser = Find(entry.first);
		bool inserted = traverser.Index == StoredData.At(traverser.Container).end(); //Checks if the value was not found and needs to be inserted
		if (inserted)
		{
			traverser.Index = StoredData.At(traverser.Container).PushBack(entry); //Value was not found, we do need to insert it.
			Population++;
		}
		return std::pair(traverser, inserted);
	}

	template <typename TKey, typename TData, typename Hash>
	std::pair<typename HashMap<TKey, TData, Hash>::Iterator, bool> HashMap<TKey, TData, Hash>::Insert(PairType&& entry)
	{
		Iterator traverser = Find(entry.first);
		bool inserted = traverser.Index == StoredData.At(traverser.Container).end(); //Checks if the value was not found and needs to be inserted
		if (inserted)
		{
			traverser.Index = StoredData.At(traverser.Container).PushBack(std::move(entry)); //Value was not found, we do need to insert it.
			Population++;
		}
		return std::pair(traverser, inserted);
	}


	template <typename TKey, typename TData, typename Hash>
	void HashMap<TKey, TData, Hash>::Remove(const TKey& targetKey)
	{
		Iterator traverser = Find(targetKey);
		if (traverser.Index != StoredData.At(traverser.Container).end())
		{
			StoredData.At(traverser.Container).Remove(traverser.Index);
			Population--;
		}
	}

	template <typename TKey, typename TData, typename Hash>
	void HashMap<TKey, TData, Hash>::Clear()
	{
		for (auto& chain : StoredData)
		{
			chain.Clear();
		}
		Population = 0;
	}
	template <typename TKey, typename TData, typename Hash>
	size_t HashMap<TKey, TData, Hash>::Size() const
	{
		return Population;
	}

	template <typename TKey, typename TData, typename Hash>
	bool HashMap<TKey, TData, Hash>::ContainsKey(const TKey& targetKey) const
	{
		ConstIterator traverser = Find(targetKey);
		return traverser.Index != StoredData.At(traverser.Container).CEnd();
	}

	template <typename TKey, typename TData, typename Hash>
	TData& HashMap<TKey, TData, Hash>::At(const TKey& targetKey)
	{
		auto findResult = Find(targetKey).Index;
		if(&findResult == nullptr)
		{
			throw std::runtime_error("Key does not exist!");
		}
		return (*findResult).second;
	}

	template <typename TKey, typename TData, typename Hash>
	const TData& HashMap<TKey, TData, Hash>::At(const TKey& targetKey) const
	{
		auto findResult = Find(targetKey).Index;
		if(&findResult == nullptr)
		{
			throw std::runtime_error("Key does not exist!");
		}
		return (*findResult).second;
	}

	template <typename TKey, typename TData, typename Hash>
	typename inline HashMap<TKey, TData, Hash>::Iterator HashMap<TKey, TData, Hash>::begin()
	{
		if (Population < 1)
		{
			return end();
		}
		size_t i = 0;
		for (i = 0; i < StoredData.Size(); ++i)
		{
			if (!StoredData.At(i).IsEmpty())
			{
				break;
			}
		}
		Iterator newIterator(i, StoredData.At(i).begin(), this);
		if (newIterator.Index == StoredData.At(i).end())
		{
			++newIterator;
		}
		return(newIterator);
	}

	template <typename TKey, typename TData, typename Hash>
	typename inline HashMap<TKey, TData, Hash>::Iterator HashMap<TKey, TData, Hash>::end()
	{
		if (Size() == 0)
		{
			return(Iterator(0, SList<PairType>::Iterator(), this));
		}
		return(Iterator(Size() - 1, SList<PairType>::Iterator(), this));
	}

	template <typename TKey, typename TData, typename Hash>
	typename inline HashMap<TKey, TData, Hash>::ConstIterator HashMap<TKey, TData, Hash>::cbegin() const
	{
		if (Population < static_cast<size_t>(1))
		{
			return cend();
		}
		size_t i = 0;
		for (i = 0; i < StoredData.Size(); ++i)
		{
			if (!StoredData.At(i).IsEmpty())
			{
				break;
			}
		}
		ConstIterator newIterator(i, StoredData.At(i).begin(), this);
		if (newIterator.Index == StoredData.At(i).end())
		{
			++newIterator;
		}
		return(newIterator);
	}

	template <typename TKey, typename TData, typename Hash>
	typename inline HashMap<TKey, TData, Hash>::ConstIterator HashMap<TKey, TData, Hash>::cend() const
	{
		if (Size() == 0)
		{
			return(ConstIterator(0, SList<PairType>::Iterator(), this));
		}
		return(ConstIterator(Size() - 1, SList<PairType>::Iterator(), this));
	}
}
