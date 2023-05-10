#pragma once
#include "Vector.h"
#include "SList.h"
#include "HashFunctor.h"
#include <utility>
#include "DefaultEquality.h"
#include <functional>
#include <memory_resource>

namespace FieaGameEngine
{
	template <typename TKey,typename TData, typename Hash = HashFunctor<TKey>>
	/// <summary>
	/// The file specifying the HashMap template class, which is used to create HashMaps that store key value pairs, composed of Vector and SList data types. Includes definition for HashMaps of a user-defined type and iterators.
	/// Includes functions to wipe, initialize, and copy HashMaps. Allows users to add new values to the HashMap, as well as iterate through and insert or remove elements between values. Additionally, includes capability to uniquely
	/// hash TKey values to convert to numbers, which may then be used to further organize the hashmap and reduce time overhead in data lookups.
	/// </summary>
	class HashMap final
	{
	public:

		using PairType = std::pair<const TKey, TData>;
		using ChainType = SList<PairType>;
		using EqualityFunctor = std::function<bool(const TKey&, const TKey&)>;
		/// <summary>
		/// The Iterator class, which can iterate through the HashMap to access data members and their associated node information. They can traverse a HashMap and be used to find and access data members.
		/// It returns a TData reference when dereferenced.
		/// </summary>
		class Iterator final
		{
		public:
			friend HashMap;
			/// <summary>
			/// The prefix increment operator that is used to traverse the HashMap associated to the Iterator. Each increment shifts the Iterator one node to the right, until one past the HashMap end is reached.
			/// </summary>
			Iterator& operator++();
			/// <summary>
			/// The postfix increment operator that is used to traverse the HashMap associated to the Iterator. Each increment shifts the Iterator one node to the right, until one past the HashMap end is reached.
			/// </summary>
			Iterator operator++(int);
			/// <summary>
			/// An override of the != (not equal to) operation for Iterator. This allows Iterators to be directly compared based on their index, container, and associated hashmap.
			/// </summary>
			/// <param name="comparedIterator">The Iterator argument comparedIterator is the iterator to be compared with the calling Iterator.</param>
			/// <returns>Returns a boolean variable inidicating whether the iterators are not equal</returns>
			bool operator!=(Iterator comparedIterator) const;
			/// <summary>
			/// An override of the == (equal to) operation for Iterator. This allows Iterators to be directly compared based on their index, container, and associated hashmap.
			/// </summary>
			/// <param name="comparedIterator">The Iterator argument comparedIterator is the iterator to be compared with the calling Iterator.</param>
			/// <returns>Returns a boolean variable inidicating whether the iterators are equal</returns>
			bool operator==(Iterator comparedIterator) const;
			/// <summary>
			/// The dereference operator that is used to access the actual data value stored inside of the position the Iterator is referencing. Returns a variable of the type TData the HashMap stores.
			/// </summary>
			PairType& operator*() const;
			/// <summary>
			/// The arrow dereference operator that is used to access the actual data value stored inside of the position the Iterator is referencing. Returns a variable of the type TData the HashMap stores.
			/// </summary>
			PairType operator->() const;
			/// <summary>
			/// A copy assignment definition for the Iterator, ensuring the calling iterator has the index, container and associated HashMap of the provided Iterator.
			/// </summary>
			void operator=(const Iterator& copiedIterator);

			/// <summary>
			/// Default constructor for Iterator that takes no arguments. Defined explicitly due to HashMap lack of direct access to SList and Vector private methods.
			/// </summary>
			Iterator();
			/// <summary>
			/// A copy constructor definition for the Iterator, ensuring the calling iterator is initialized with the index, container and associated HashMap of the provided Iterator.
			/// </summary>
			/// <param name="copiedIterator">The Iterator to be copied</param>
			Iterator(const Iterator& copiedIterator);
			/// <summary>
			/// The destructor for the Iterator. Defaults all associated values to ensure lack of access.
			/// </summary>
			~Iterator();
		private:
			/// <summary>
			/// The index that the Iterator resides at in the HashMap's internal vector. Used as an organizational mechanism to lower time overhead when searching for data values.
			/// </summary>
			size_t Container = 0;
			/// <summary>
			/// The exact position in the Vector's internal SList inside the HashMap that the iterator is associated to. Functions as an SList Iterator.
			/// </summary>
			typename ChainType::Iterator Index;
			/// <summary>
			/// The hashmap that the Iterator is associated with. Represented as a HashMap pointer variable.
			/// </summary>
			HashMap* Owner = nullptr;
			/// <summary>
			/// An Iterator constructor that takes in arguments for the container, index, and owner to fully define the Iterator on initialization.
			/// </summary>
			Iterator(size_t container, typename SList<PairType>::Iterator index, HashMap* owner);
		};
		/// <summary>
		/// The ConstIterator class, which can iterate through the HashMap to access data members and their associated node information. They can traverse a HashMap and be used to find and access data members.
		/// It returns a const TData reference when dereferenced.
		/// </summary>
		class ConstIterator final
		{
		public:
			friend HashMap;
			/// <summary>
			/// The prefix increment operator that is used to traverse the HashMap associated to the ConstIterator. Each increment shifts the ConstIterator one node to the right, until one past the HashMap end is reached.
			/// </summary>
			const ConstIterator& operator++();
			/// <summary>
			/// The postfix increment operator that is used to traverse the HashMap associated to the Iterator. Each increment shifts the Iterator one node to the right, until one past the HashMap end is reached.
			/// </summary>
			ConstIterator operator++(int);
			/// <summary>
			/// An override of the != (not equal to) operation for ConstIterator. This allows ConstIterators to be directly compared based on their index, container, and associated hashmap.
			/// </summary>
			/// <param name="comparedIterator">The ConstIterator argument comparedIterator is the ConstIterator to be compared with the calling ConstIterator.</param>
			/// <returns>Returns a boolean variable inidicating whether the ConstIterators are not equal</returns>
			bool operator!=(ConstIterator comparedIterator) const;
			/// <summary>
			/// An override of the == (equal to) operation for ConstIterator. This allows ConstIterators to be directly compared based on their index, container, and associated hashmap.
			/// </summary>
			/// <param name="comparedIterator">The ConstIterator argument comparedIterator is the ConstIterator to be compared with the calling ConstIterator.</param>
			/// <returns>Returns a boolean variable inidicating whether the ConstIterators are equal</returns>
			bool operator==(ConstIterator comparedIterator) const;
			/// <summary>
			/// The dereference operator that is used to access the actual data value stored inside of the position the ConstIterator is referencing. Returns a variable of the type const TData the HashMap stores.
			/// </summary>
			const PairType& operator*() const;
			/// <summary>
			/// The arrow dereference operator that is used to access the actual data value stored inside of the position the ConstIterator is referencing. Returns a variable of the type const TData the HashMap stores.
			/// </summary>
			const PairType& operator->() const;
			/// <summary>
			/// A copy assignment definition for the ConstIterator, ensuring the calling ConstIterator has the index, container and associated HashMap of the provided ConstIterator.
			/// </summary>
			void operator=(const ConstIterator& copiedIterator);

			/// <summary>
			/// Default constructor for ConstIterator that takes no arguments. Defined explicitly due to HashMap lack of direct access to SList and Vector private methods.
			/// </summary>
			ConstIterator();
			/// <summary>
			/// A copy constructor definition for the ConstIterator, ensuring the calling ConstIterator is initialized with the index, container and associated HashMap of the provided ConstIterator.
			/// </summary>
			/// <param name="copiedIterator">The ConstIterator to be copied</param>
			ConstIterator(const ConstIterator& copiedIterator);
			/// <summary>
			/// The destructor for the ConstIterator. Defaults all associated values to ensure lack of access.
			/// </summary>
			~ConstIterator();
		private:
			/// <summary>
			/// The index that the ConstIterator resides at in the HashMap's internal vector. Used as an organizational mechanism to lower time overhead when searching for data values.
			/// </summary>>
			size_t Container = 0;
			/// <summary>
			/// The exact position in the Vector's internal SList inside the HashMap that the ConstIterator is associated to. Functions as an SList Iterator.
			/// </summary>
			typename ChainType::ConstIterator Index;
			/// <summary>
			/// The hashmap that the ConstIterator is associated with. Represented as a HashMap pointer variable.
			/// </summary>
			const HashMap* Owner = nullptr;
			/// <summary>
			/// An ConstIterator constructor that takes in arguments for the container, index, and owner to fully define the Iterator on initialization.
			/// </summary>
			ConstIterator(size_t container, typename SList<PairType>::ConstIterator index, const HashMap* owner);
		};
	public:
		/// <summary>
		/// A default constructor for the HashMap. Allows the user to specify the number of containers that the HashMap should hold, defaulting to 13 otherwise.
		/// </summary>
		explicit HashMap(size_t size = 13);
		/// <summary>
		/// A destructor for the HashMap. Wipes all associated values to ensure lack of access to invalid data.
		/// </summary>
		~HashMap(); //= default;
		/// <summary>
		/// The copy constructor for the HashMap. It is defaulted because the class it is dependent on, Vector, has a working implementation
		/// </summary>
		HashMap(const HashMap & copiedMap) = default;
		/// <summary>
		/// The move constructor for the HashMap. It is defaulted because the class it is dependent on, Vector, has a working implementation
		/// </summary>
		HashMap(HashMap&&) noexcept = default;
		/// <summary>
		/// The bracket operator to access values in the HashMap based on the user-provided key. Upon entry of a TKey, the HashMap will search for its associated value, returning a TData& reference on completion.
		/// </summary>
		TData& operator[](const TKey targetKey);

		HashMap& operator=(HashMap&&) noexcept;


		/// <summary>
		/// The non-const Find function that accepts a key and then searches the HashMap for its match, returning an Iterator that points to the target key-value pair's position in the HashMap. Accepts a const TKey reference parameter and
		/// allows additional argument specifying a custom equality functor definition.
		/// </summary>
		Iterator Find(const TKey& key, EqualityFunctor equalityFunctor = DefaultEquality<TKey>{});
		/// <summary>
		/// The const Find function that accepts a key and then searches the HashMap for its match, returning a ConstIterator that points to the target key-value pair's position in the HashMap. Accepts a const TKey reference parameter and
		/// allows additional argument specifying a custom equality functor definition.
		/// </summary>
		ConstIterator Find(const TKey& key, EqualityFunctor equalityFunctor = DefaultEquality<TKey>{}) const;// = DefaultEquality{}) const;
		/// <summary>
		/// Accepts a constant key-value pair reference, then searches the HashMap to see whether or not it exists. If it does not already exist, the new value is added at the position determined by the hashed key. Otherwise, the matching
		/// key's existing argument is returned instead. Returns a pair, including an iterator that points to the target position, as well as a boolean that specifies whether a new value was inserted or not.
		/// </summary>
		std::pair<Iterator, bool> Insert(const PairType& entry);
		std::pair<Iterator, bool> Insert(PairType&& entry);

		/// <summary>
		/// Removes the key value pair tied to the specified key from the HashMap, if it exists. Accepts a single constant TKey reference, removing the element if found, and doing nothing otherwise. Returns nothing.
		/// </summary>
		void Remove(const TKey& targetKey);
		/// <summary>
		/// Clears every value from the HashMap, additionally freeing all reserved memory from the HashMap.
		/// </summary>
		void Clear();

		/// <summary>
		/// Returns the population of the HashMap as a size_t, the number of total key-value pairs currently stored within the HashMap, irrespective of the containers these key-value pairs are primarily stored in.
		/// </summary>
		size_t Size() const;
		/// <summary>
		/// Accepts a const TKey reference variable, then returns whether or not the HashMap contains the specified key currently.
		/// </summary>
		bool ContainsKey(const TKey& targetKey) const;

		/// <summary>
		/// Used to find the data value associated with a provided key. Accepts a const TKey reference value, returning a TData reference variable that is associated with the specified key.
		/// </summary>
		TData& At(const TKey& targetKey);
		/// <summary>
		/// A constant method used to find the data value associated with a provided key. Accepts a const TKey reference value, returning a const TData reference variable that is associated with the specified key.
		/// </summary>
		const TData& At(const TKey& targetKey) const;

		/// <summary>
		/// Returns an Iterator that's associated with the first element in the hashmap, based on container as well as internal position. If no elements exist in the HashMap, an exception is thrown.
		/// </summary>
		Iterator begin();
		/// <summary>
		/// Returns an Iterator pointing past the end of the HashMap.
		/// </summary>
		Iterator end();

		/// <summary>
		/// Returns a ConstIterator that's associated with the first element in the hashmap, based on container as well as internal position. If no elements exist in the HashMap, an exception is thrown.
		/// </summary>
		ConstIterator cbegin() const;
		/// <summary>
		/// Returns a ConstIterator pointing past the end of the HashMap.
		/// </summary>
		ConstIterator cend() const;
	private:
		/// <summary>
		/// The StoredData variable, used to hold the Vector that makes up the HashMap. Stores SLists at each index.
		/// </summary>
		typename Vector<ChainType> StoredData;

		/// <summary>
		/// The population variable, used to store how many elements are stored within the HashMap.
		/// </summary>
		size_t Population = 0;
	};
}
#include "HashMap.inl"