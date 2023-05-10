#pragma once
#include <cstddef>
#include <memory>
#include <assert.h>
#include <limits>
#include <stdexcept>
#include <iterator>
/// <summary>
/// The file specifying the Vector template class, which is used to create Vectors that can be traversed in either direction. Includes definition for Vectors of a user-defined type and iterators. Includes functions to wipe, initialize,
/// and copy Vectors. Allows users to push and pop data values onto the Vector, as well as iterate through and insert or remove elements between values.
/// </summary>
namespace FieaGameEngine
{
	template <typename T>
	/// <summary>
	/// The Vector class is used to access a full list of elements, allowing access to those at any specified index at any time. Allows the specificaiton of capacity and removal of values, as well as addition
	/// of new ones. Also allows searching by specified values, and accepts elements of any given type for the Vector.
	/// </summary>
	/// 
	class Vector final
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = std::size_t;
		using rvalue_reference = value_type&&;
		/// <summary>
		/// The Iterator class, which can iterate through the Vector to access data members and their associated node information. They can traverse a Vector, be used to find and access data members, and 
		/// be converted to the ConstIterator class via typecast. It returns a T reference when dereferenced.
		/// </summary>
		
		class Iterator final
		{
		public:
			using size_type = Vector::size_type;
			using difference_type = std::ptrdiff_t;
			using value_type = Vector::value_type;
			using reference = Vector::reference;
			using rvalue_reference = Vector::rvalue_reference;
			using pointer = value_type*;
			using iterator_category = std::random_access_iterator_tag;

				friend Vector;
				friend class ConstIterator;

				/// <summary>
				/// Default constructor for Iterator that takes no arguments. Since all member variables are defaulted to nullptr, another defined constructor is unnecessary.
				/// </summary>
				Iterator() = default;
				/// <summary>
				/// Copy constructor for the Iterator, takes in an Iterator to copy as an argument. Makes a deep copy, so changes made to one Iterator will not apply to the other following construction
				/// </summary>
				/// <param name="copiedIterator">The iterator to be copied to the iterator being constructed.</param>
				Iterator(const Iterator& copiedIterator) = default;

				/// <summary>
				/// An override of the == (equal to) operation for Iterator. This allows Iterators to be directly compared based on their index and their associated Vectors.
				/// </summary>
				/// <param name="comparedIterator">The Iterator argument comparedIterator is the iterator to be compared with the calling Iterator.</param>
				/// <returns>Returns a boolean variable inidicating whether the iterators are equal</returns>
				bool operator==(Iterator comparedIterator) const;	
				/// <summary>
				/// An override of the != (not equal to) operation for Iterator. This allows Iterators to be directly compared based on their index and their associated Vectors.
				/// </summary>
				/// <param name="comparedIterator">The Iterator argument comparedIterator is the iterator to be compared with the calling Iterator.</param>
				/// <returns>Returns a boolean variable inidicating whether the iterators are not equal</returns>
				bool operator!=(Iterator comparedIterator) const;
				/// <summary>
				/// The prefix increment operator that is used to traverse the Vector associated to the Iterator. Each increment shifts the Iterator one node to the right, until one past the Vector end is reached and its index is equal to the Vector size.
				/// </summary>
				Iterator& operator++();
				/// <summary>
				/// The postfix increment operator that is used to traverse the Vector associated to the Iterator. Each increment shifts the Iterator one node to the right, until one past the Vector end is reached and its index is equal to the Vector size.
				/// </summary>
				Iterator operator++(int);
				/// <summary>
				/// The prefix decrement operator that is used to traverse the Vector associated to the Iterator. Each increment shifts the Iterator one node to the left, until the Vector beginning is reached and its index is equal to 0.
				/// </summary>
				Iterator& operator--();
				/// <summary>
				/// The postfix decrement operator that is used to traverse the Vector associated to the Iterator. Each increment shifts the Iterator one node to the left, until the Vector beginning is reached and its index is equal to 0.
				/// </summary>
				Iterator operator--(int);

				/// <summary>
				/// The plus equal integer operator, which allows a user to increment the index pointed to by the Iterator by supplying an integer value in the format "iterator += integer". If adding the integer would push the iterator
				/// beyond the Vector's size, the iterator is set to the end of the Vector, not proceeding beyond.
				/// </summary>
				Iterator& operator+=(size_type increment);
				/// <summary>
				/// The minus equal integer operator, which allows a user to decrement the index pointed to by the Iterator by supplying an integer value in the format "iterator -= integer". If subtracting the integer would push the iterator
				/// before the Vector start, the iterator is set to the beginning of the Vector, not leaving it.
				/// </summary>
				Iterator& operator-=(size_type decrement);
				/// <summary>
				/// The plus equal iterator operator, which allows a user to increment the index pointed to by the Iterator by supplying an iterator value in the format "iterator += itrator". If adding the index of the provided iterator would
				/// push the calling iterator's index beyond the Vector's size, the iterator is set to the end of the Vector, not proceeding beyond.
				/// </summary>
				Iterator& operator+=(Iterator increment);
				/// <summary>
				/// The minus equal iterator operator, which allows a user to decrement the index pointed to by the Iterator by supplying an iterator value in the format "iterator -= itrator". If subtracting the index of the provided iterator would
				/// push the calling iterator's index below 0, the iterator is set to the start of the array, not proceeding beyond.
				/// </summary>
				Iterator& operator-=(Iterator increment);

				/// <summary>
				/// The plus integer operator, which allows a user to return a new iterator with an index derrived from supplying an integer value in the format "iterator + integer". If adding the integer would push the iterator
				/// beyond the Vector's size, the iterator is set to the end of the Vector, not proceeding beyond.
				/// </summary>
				Iterator operator+(size_type increment);
				/// <summary>
				/// The minus integer operator, which allows a user to return a new iterator with an index derrived from supplying an integer value in the format "iterator - integer". If subtracting the integer would push the iterator
				/// before the Vector start, the iterator is set to the beginning of the Vector, not leaving it.
				/// </summary>
				Iterator operator-(size_type decrement);
				/// <summary>
				/// The plus iterator operator, which allows a user to return a new iterator with an index derrived from supplying an iterator value in the format "iterator + iterator". If adding the index of the provided iterator would
				/// push the calling iterator's index beyond the Vector's size, the iterator is set to the end of the Vector, not proceeding beyond.
				/// </summary>
				Iterator operator+(Iterator& increment);
				/// <summary>
				/// The minus iterator operator, which allows a user to return a new iterator with an index derrived from supplying an iterator value in the format "iterator - iterator". If subtracting the index of the provided iterator would
				/// push the calling iterator's index below 0, the iterator is set to the start of the array, not proceeding beyond.
				/// </summary>
				Iterator operator-(Iterator& increment);
				/// <summary>
				/// The dereference operator that is used to access the actual value stored inside of the position the Iterator is referencing. Returns a variable of the type T that the Vector carries.
				/// </summary>
				reference operator*() const;
				/// <summary>
				/// A copy assignment definition for the Iterator, ensuring the calling iterator has the index and associated vector of the provided Iterator.
				/// </summary>
				void operator=(const Iterator& copiedIterator);
					
			private:
				/// <summary>
				/// Defined constructor that accepts arguments to specify the Vector owner and associated index of the Iterator. This allows immediate user-specified initialization of the Iterator.
				/// </summary>
				/// <param name="container">Represents the Vector that is associated to the Iterator</param>
				/// <param name="indexValue">Represents the index that the iterator is associated with</param>
				Iterator(Vector& container, size_type indexValue);
				/// <summary>
				/// The Owner variable carries a pointer to the Vector associated with the iterator. This ensures Iterators can only be used in operations relating to their own Vector.
				/// </summary>
				Vector* Owner = nullptr;
				/// <summary>
				/// The Index variable contains a size_t value specifying the index in the Vector the iterator is associated with. Lets the iterator maintain its place in the Vector.
				/// </summary>
				size_type Index = 0;
		};
		/// <summary>
		/// The ConstIterator class, which can iterate through the Vector to access data members. They can traverse a Vector and be used to find and access data members.
		/// It returns a const T reference when dereferenced.
		/// </summary>
		class ConstIterator final
		{
			using size_type = Vector::size_type;
			using difference_type = std::ptrdiff_t;
			using value_type = Vector::value_type;
			using reference = Vector::reference;
			using rvalue_reference = Vector::rvalue_reference;
			using pointer = value_type*;
			using iterator_category = std::random_access_iterator_tag;
			public:
				friend Vector;
				friend class Iterator;
				/// <summary>
				/// Default constructor for ConstIterator that takes no arguments. Since all member variables are defaulted to nullptr, another defined constructor is unnecessary.
				/// </summary>
				ConstIterator() = default;
				/// <summary>
				/// Copy constructor for the ConstIterator, takes in an Iterator to copy as an argument. Makes a deep copy, so changes made to one ConstIterator will not apply to the other following construction
				/// </summary>
				/// <param name="copiedIterator">The constiterator to be copied to the constiterator being constructed.</param>
				ConstIterator(const ConstIterator& copiedIterator) = default;

				/// <summary>
				/// An override of the == (equal to) operation for ConstIterator. This allows ConstIterators to be directly compared based on their index and their associated Vectors.
				/// </summary>
				/// <param name="comparedIterator">The ConstIterator argument comparedIterator is the constiterator to be compared with the calling ConstIterator.</param>
				/// <returns>Returns a boolean variable inidicating whether the constiterators are equal</returns>
				bool operator==(ConstIterator comparedIterator) const;
				/// <summary>
				/// An override of the != (not equal to) operation for ConstIterator. This allows ConstIterators to be directly compared based on their index and their associated Vectors.
				/// </summary>
				/// <param name="comparedIterator">The ConstIterator argument comparedIterator is the constiterator to be compared with the calling ConstIterator.</param>
				/// <returns>Returns a boolean variable inidicating whether the constiterators are not equal</returns>
				bool operator!=(ConstIterator comparedIterator) const;
				/// <summary>
				/// The prefix increment operator that is used to traverse the Vector associated to the ConstIterator. Each increment shifts the ConstIterator one node to the right, until one past the Vector end is reached and its index is equal to the Vector size.
				/// </summary>
				ConstIterator& operator++();
				/// <summary>
				/// The postfix increment operator that is used to traverse the Vector associated to the ConstIterator. Each increment shifts the ConstIterator one node to the right, until one past the Vector end is reached and its index is equal to the Vector size.
				/// </summary>
				ConstIterator operator++(int);
				/// <summary>
				/// The prefix decrement operator that is used to traverse the Vector associated to the ConstIterator. Each increment shifts the ConstIterator one node to the left, until the Vector beginning is reached and its index is equal to 0.
				/// </summary>
				ConstIterator& operator--();
				/// <summary>
				/// The postfix decrement operator that is used to traverse the Vector associated to the ConstIterator. Each increment shifts the ConstIterator one node to the left, until the Vector beginning is reached and its index is equal to 0.
				/// </summary>
				ConstIterator operator--(int);

				/// <summary>
				/// The plus equal integer operator, which allows a user to increment the index pointed to by the ConstIterator by supplying an integer value in the format "constiterator += integer". If adding the integer would push the constiterator
				/// beyond the Vector's size, the constiterator is set to the end of the Vector, not proceeding beyond.
				/// </summary>
				ConstIterator& operator+=(const size_type increment);
				/// <summary>
				/// The minus equal integer operator, which allows a user to decrement the index pointed to by the ConstIterator by supplying an integer value in the format "constiterator -= integer". If subtracting the integer would push the constiterator
				/// before the Vector start, the constiterator is set to the beginning of the Vector, not leaving it.
				/// </summary>
				ConstIterator& operator-=(const size_type decrement);
				/// <summary>
				/// The plus equal constiterator operator, which allows a user to increment the index pointed to by the ConstIterator by supplying a constiterator value in the format "constiterator += constiterator". If adding the index of the provided constiterator would
				/// push the calling constiterator's index beyond the Vector's size, the constiterator is set to the end of the Vector, not proceeding beyond.
				/// </summary>
				ConstIterator& operator+=(const ConstIterator increment);
				/// <summary>
				/// The minus equal constiterator operator, which allows a user to decrement the index pointed to by the ConstIterator by supplying a constiterator value in the format "constiterator -= constitrator". If subtracting the index of the provided constiterator would
				/// push the calling constiterator's index below 0, the constiterator is set to the start of the array, not proceeding beyond.
				/// </summary>
				ConstIterator& operator-=(const ConstIterator increment);

				/// <summary>
				/// The plus integer operator, which allows a user to return a new constiterator with an index derrived from supplying an integer value in the format "constiterator + integer". If adding the integer would push the constiterator
				/// beyond the Vector's size, the constiterator is set to the end of the Vector, not proceeding beyond.
				/// </summary>
				ConstIterator operator+(const size_type increment);
				/// <summary>
				/// The minus integer operator, which allows a user to return a new constiterator with an index derrived from supplying an integer value in the format "constiterator - integer". If subtracting the integer would push the constiterator
				/// before the Vector start, the constiterator is set to the beginning of the Vector, not leaving it.
				/// </summary>
				ConstIterator operator-(const size_type decrement);
				/// <summary>
				/// The plus constiterator operator, which allows a user to return a new constiterator with an index derrived from supplying an constiterator value in the format "constiterator + constiterator". If adding the index of the provided constiterator would
				/// push the calling constiterator's index beyond the Vector's size, the constiterator is set to the end of the Vector, not proceeding beyond.
				/// </summary>
				ConstIterator operator+(const ConstIterator& increment);
				/// <summary>
				/// The minus constiterator operator, which allows a user to return a new constiterator with an index derrived from supplying a constiterator value in the format "constiterator - constiterator". If subtracting the index of the provided constiterator would
				/// push the calling constiterator's index below 0, the constiterator is set to the start of the array, not proceeding beyond.
				/// </summary>
				ConstIterator operator-(const ConstIterator& increment);
				/// <summary>
				/// The dereference operator that is used to access the actual value stored inside of the position the CosntIterator is referencing. Returns a const reference of the type T that the Vector carries.
				/// </summary>
				const_reference operator*() const;
				/// <summary>
				/// A copy assignment definition for the ConstIterator, ensuring the calling constiterator has the index and associated vector of the provided ConstIterator.
				/// </summary>
				void operator=(const ConstIterator& copiedIterator);
				/// <summary>
				/// Type-cast constructor that allows an Iterator to be converted to the ConstIterator type.
				/// </summary>
				/// <param name="convertedIterator">Represents the Iterator that is being cast to the ConstIterator type.</param>
				ConstIterator(const Iterator& convertedIterator);

			private:
				/// <summary>
				/// Defined constructor that accepts arguments to specify the Vector owner and associated index of the ConstIterator. This allows immediate user-specified initialization of the ConstIterator.
				/// </summary>
				/// <param name="container">Represents the Vector that is associated to the ConstIterator</param>
				/// <param name="indexValue">Represents the index that the constiterator is associated with</param>
				ConstIterator(Vector* container, size_type indexValue);
				/// <summary>
				/// The Owner variable carries a pointer to the Vector associated with the constiterator. This ensures ConstIterators can only be used in operations relating to their own Vector.
				/// </summary>
				Vector* Owner = nullptr;
				/// <summary>
				/// The Index variable contains a size_t value specifying the index in the Vector the constiterator is associated with. Lets the constiterator maintain its place in the Vector.
				/// </summary>
				size_type Index = 0;
		};
		private:
			/// <summary>
			/// The size of the vector shows how many elements are currently occupying it. This can be incremented and decremented by adding or removing data members from it.
			/// </summary>
			size_type VectorSize = size_t(0);
			/// <summary>
			/// The capacity of the vector shows how many elements the vector can hold with the storage it has been allocated. It can be increased by reserving more, and decreased by using ShrinkToFit().
			/// </summary>
			size_type VectorCapacity = size_t(0);
			/// <summary>
			/// A pointer to the start of the Vector. Stored to allow access to any element inside the Vector.
			/// </summary>
			pointer VectorData = nullptr;

		public:
			friend Iterator;
			friend ConstIterator;
			/// <summary>
			/// Default constructor for Vector that takes no arguments. Since all member variables are defaulted to nullptr and 0, another defined constructor is unnecessary.
			/// </summary>
			Vector() = default;
			/// <summary>
			/// The Vector's move constructor. Used to make a shallow copy of the Vector provided as an argument. Upon completion, the Vector argument provided is unusable, and a full copy of it is accessible through the calling Vector.
			/// </summary>
			Vector(Vector&&) noexcept; //Move constructor
			/// <summary>
			/// The Vector's move assignment operator. Used to make a shallow copy of the Vector provided as an argument. Upon completion, the Vector argument provided is unusable, and a full copy of it is accessible through the calling Vector.
			/// </summary>
			Vector& operator=(Vector&&) noexcept; //Move assignment operator
			/// <summary>
			/// The destructor for the Vector. Frees all storage previously allocated to it and defaults all associated data.
			/// </summary>
			~Vector();
			/// <summary>
			/// The copy constructor defined for the Vector. Makes a deep copy of the vector provided as an argument within the calling vector. Upon completion, both the argument and calling Vector can be manipulated without influencing the other.
			/// </summary>
			Vector(const Vector& copiedVector); //Copy constructor declaration
			
			/// <summary>
			/// The [] operator, used to access elements stored at each index of the array. Returns the T& object allocated to the specified index. Begins at 0 and continues to Vector size-1.
			/// </summary>
			reference operator[](const size_type index);
			/// <summary>
			/// The constant [] operator, used to access elements stored at each index of the array. Returns the T& object allocated to the specified index. Begins at 0 and continues to Vector size-1.
			/// </summary>
			reference operator[](const size_type index) const;
			/// <summary>
			/// The copy assignment operator defined for the Vector. Makes a deep copy of the vector provided as an argument within the calling vector. Upon completion, both the argument and calling Vector can be manipulated without influencing the other.
			/// </summary>
			void operator=(const Vector& copiedVector);

			/// <summary>
			/// Returns the T object positioned at the index provided as an argument. Used to access elements stored within the Vector similarly to the [] operator.
			/// </summary>
			reference At(const size_type index);
			/// <summary>
			/// A constant method that returns the T object positioned at the index provided as an argument. Used to access elements stored within the Vector similarly to the [] operator.
			/// </summary>
			reference At(const size_type index) const;

			/// <summary>
			/// Removes the element at the back of the Vector, deleting its associated data and decrementing the Vector's size.
			/// </summary>
			void PopBack();
			/// <summary>
			/// Pushes a new element to the back of the Vector, adding its data and incrementing the Vector's size.
			/// </summary>
			void PushBack(const_reference newItem);
			void PushBack(rvalue_reference newItem);
			/// <summary>
			/// Returns a boolean indicating whether or not the calling Vector is empty, that is, has no elements.
			/// </summary>
			bool IsEmpty() const;

			/// <summary>
			/// Returns a reference to the item stored at the front of the Vector.
			/// </summary>
			reference Front();
			/// <summary>
			/// Returns a reference to the item stored at the back of the Vector.
			/// </summary>
			reference Back();
			/// <summary>
			/// A const function that returns a reference to the item stored at the front of the Vector.
			/// </summary>
			reference Front() const;
			/// <summary>
			/// A const function that returns a reference to the item stored at the back of the Vector.
			/// </summary>
			reference Back() const;

			/// <summary>
			/// Returns the size of the vector, how many items it is currently holding.
			/// </summary>
			size_type Size() const;
			/// <summary>
			/// Returns the capacity of the vector, how many items it is capable of holding currently.
			/// </summary>
			size_type Capacity() const;

			/// <summary>
			/// Used to allocate more space to the vector. Argument specifies how many elements the Vector should be able to hold.
			/// </summary>
			void Reserve(const size_type elements);
			/// <summary>
			/// Used to shrink the capacity of the Vector to match its size.
			/// </summary>
			void ShrinkToFit();

			Iterator Find(const_reference targetValue) const;
			/// <summary>
			/// When provided a target value, returns an Iterator pointing to where that value is stored in the array, returning an iterator to the end otherwise
			/// </summary>
			Iterator Find(const_reference targetValue);
			/// <summary>
			/// Deletes every item in the array, decrementing size to 0 and allowing space to be assigned to new elements.
			/// </summary>
			void Clear();

			/// <summary>
			/// Accepts an element of the type associated with the Vector, removing the first instance of this element from the vector if it exists.
			/// </summary>
			bool Remove(const_reference elementRemoved);
			/// <summary>
			/// Accepts an iterator element, removing the element it points to from the vector if it exists.
			/// </summary>
			bool Remove(const Iterator& position);
			/// <summary>
			/// Accepts a constiterator element, removing the element it points to from the vector if it exists.
			/// </summary>
			bool Remove(const ConstIterator& position);
			/// <summary>
			/// Accepts two iterator elements, one pointing to the front and one pointing to the back, defining a data range to be removed from the Vector, inclusively.
			/// </summary>
			bool Remove(const Iterator& start, const Iterator& end);
			/// <summary>
			/// Accepts two constiterator elements, one pointing to the front and one pointing to the back, defining a data range to be removed from the Vector, inclusively.
			/// </summary>
			bool Remove(const ConstIterator& start, const ConstIterator& end);

			/// <summary>
			/// Returns an Iterator object that is associated to the front of the Vector.
			/// </summary>
			Iterator begin();
			/// <summary>
			/// Returns an Iterator object that is associated to the end of the Vector.
			/// </summary>
			Iterator end();
			/// <summary>
			/// Returns a ConstIterator object that is associated to the front of the Vector.
			/// </summary>
			ConstIterator cbegin();
			/// <summary>
			// Returns a ConstIterator object that is associated to the end of the Vector.
			/// </summary>
			ConstIterator cend();
	};
}
#include "Vector.inl"