#pragma once
#include <cstdint>
#include <cstddef>
/// <summary>
/// The file specifying the SList template class, which is used to create Singly Linked Lists that can be traversed in the forward direction. Includes definition for nodes of a user-defined type and iterators. Includes functions to wipe, initialize,
/// and copy SLists. Allows users to push and pop data values onto the SList, as well as iterate through and insert nodes between values.
/// </summary>
namespace FieaGameEngine
{
	template <typename T>
	class SList final
	{
	public:
		SList(); //Default constructor
		SList(const SList& copiedList); //Copy constructor declaration
		SList(SList&& other) noexcept; //Copy constructor declaration
		SList& operator=(const SList& copiedList); //Operator override declaration
		SList& operator=(SList&& other); //Operator override declaration
		~SList(); //Destructor declaration

	private:
		struct Node
		{
			Node* next{ nullptr };
			T value;
			Node(const T& data, SList<T>::Node* newLink = nullptr);
			Node(T&& data, SList<T>::Node* newLink = nullptr);
		};

	public:
		/// <summary>
		/// The Iterator class, which can iterate forward (but not backward) through the list to access data members and their associated node information. They can traverse a list, be used to find and access data members, and 
		/// be converted to the ConstIterated class via typecast. It returns a T reference when dereferenced.
		/// </summary>
		class Iterator final
		{
			private:
				friend SList<T>;
				friend class ConstIterator;

				/// <summary>
				/// The StoredValue is a pointer to the node located at the Iterator's position. It allows the Iterator to reference the data it's associated with. It is defaulted to nullptr.
				/// </summary>
				Node* StoredValue = nullptr;
				/// <summary>
				/// The owner is the SList that the Iterator is associated with. It is used to verify that any SList operations requiring an Iterator argument involve an Iterator that is tied to it, ensuring no Iterator tied to
				/// a different SList is assumed to be associated.
				/// </summary>
				const SList* Owner = nullptr;
				/// <summary>
				/// Defined constructor that accepts arguments to specify the SList owner and the associated node of the Iterator. This allows immediate user-specified initialization of the Iterator.
				/// </summary>
				/// <param name="container">Represents the SList that is associated to the Iterator</param>
				/// <param name="nodeValue">Represents the data value node that is associated to the Iterator</param>
				Iterator(const SList<T>* container, Node* nodeValue);
				~Iterator() = default;

			public:
				/// <summary>
				/// Default constructor for Iterator that takes no arguments. Since all member variables are defaulted to nullptr, another defined constructor is unnecessary.
				/// </summary>
				Iterator() = default;
				/// <summary>
				/// An override of the != (not equal to) operation for Iterator. This allows Iterators to be directly compared based on the pointers of their data and their associated SLists.
				/// </summary>
				/// <param name="comparedOperator">The Iterator& argument comparedOperator is the iterator to be compared with the calling Iterator.</param>
				/// <returns>Returns a boolean variable inidicating whether the iterators are not equal</returns>
				[[nodiscard]]bool operator!=(Iterator comparedOperator) const;
				/// <summary>
				/// An override of the == (equal to) operation for Iterator. This allows Iterators to be directly compared based on the pointers of their data and their associated SLists.
				/// </summary>
				/// <param name="comparedOperator">The Iterator& argument comparedOperator is the iterator to be compared with the calling Iterator.</param>
				/// <returns>Returns a boolean variable inidicating whether the iterators are equal</returns>
				[[nodiscard]]bool operator==(Iterator comparedOperator) const;
				/// <summary>
				/// The prefix increment operator that is used to traverse the SList associated to the Iterator. Each increment shifts the Iterator one node to the right, until one past the SList end is reached and the node pointer is nullptr.
				/// </summary>
				Iterator& operator++();
				/// <summary>
				///  The postfix increment operator that is used to traverse the SList associated to the Iterator. Each increment shifts the Iterator one node to the right, until one past the SList end is reached and the node pointer is nullptr.
				/// </summary>
				Iterator operator++(int32_t);
				/// <summary>
				/// The dereference operator that is used to access the actual value stored inside of the Node that the Iterator is referencing. Returns a variable of the type T that the Node carries.
				/// </summary>
				[[nodiscard]] T& operator*() const; 
		};

		/// <summary>
		/// The ConstIterator class, which can iterate forward (but not backward) through the list to access data members and their associated node information. They can traverse a list and access or find data members.
		/// It returns a const T reference when dereferenced.
		/// </summary>
		class ConstIterator final
		{
			private:
				friend SList<T>;
				/// <summary>
				/// The StoredValue is a pointer to the node located at the ConstIterator's position. It allows the ConstIterator to reference the data it's associated with. It is defaulted to nullptr.
				/// </summary>
				Node* StoredValue = nullptr;
				/// <summary>
				/// The owner is the SList that the ConstIterator is associated with. It is used to verify that any SList operations requiring an ConstIterator argument involve an ConstIterator that is tied to it, ensuring no ConstIterator
				/// tied to a different SList is assumed to be associated.
				/// </summary>
				const SList* Owner = nullptr;

				/// <summary>
				/// Defined constructor that accepts arguments to specify the SList owner and the associated node of the ConstIterator. This allows immediate user-specified initialization of the ConstIterator.
				/// </summary>
				/// <param name="container">Represents the SList that is associated to the ConstIterator</param>
				/// <param name="nodeValue">Represents the data value node that is associated to the ConstIterator</param>
				ConstIterator(const SList<T>* container, Node* nodeValue);
			
			public:
				/// <summary>
				/// Default constructor for ConstIterator that takes no arguments. Since all member variables are defaulted to nullptr, another defined constructor is unnecessary.
				/// </summary>
				ConstIterator() = default;
				/// <summary>
				/// Type-cast constructor that allows an Iterator to be converted to the ConstIterator type.
				/// </summary>
				/// <param name="convertedIterator">Represents the Iterator that is being cast to the ConstIterator type.</param>
				ConstIterator(const Iterator& convertedIterator);
				/// <summary>
				/// An override of the != (not equal to) operation for ConstIterator. This allows ConstIterators to be directly compared based on the pointers of their data and their associated SLists.
				/// </summary>
				/// <param name="comparedOperator">The const ConstIterator argument comparedOperator is the iterator to be compared with the calling Iterator.</param>
				/// <returns>Returns a boolean variable inidicating whether the iterators are not equal</returns>				
				[[nodiscard]]bool operator!=(ConstIterator comparedOperator) const;
				/// <summary>
				/// An override of the == (equal to) operation for ConstIterator. This allows ConstIterators to be directly compared based on the pointers of their data and their associated SLists.
				/// </summary>
				/// <param name="comparedOperator">The ConstIterator argument comparedOperator is the ConstIterator to be compared with the calling ConstIterator.</param>
				/// <returns>Returns a boolean variable inidicating whether the iterators are equal</returns>
				[[nodiscard]]bool operator==(ConstIterator comparedOperator) const;
				/// <summary>
				/// The prefix increment operator that is used to traverse the SList associated to the ConstIterator. Each increment shifts the CosntIterator one node to the right, until one past the SList end is reached and the node pointer
				/// is nullptr.
				/// </summary>
				ConstIterator& operator++();
				/// <summary>
				/// The postfix increment operator that is used to traverse the SList associated to the ConstIterator. Each increment shifts the ConstIterator one node to the right, until one past the SList end is reached and the node pointer
				/// is nullptr.
				/// </summary>
				ConstIterator operator++(int32_t);
				/// <summary>
				/// The dereference operator that is used to access the actual value stored inside of the Node that the ConstIterator is referencing.
				/// <returns>T& variable of the type the SList carries</returns>
				/// </summary>
				[[nodiscard]]const T& operator*() const;
		};

	private:
		Node* front = nullptr;
		Node* back = nullptr;
		std::size_t _size = size_t(0);

	public:

		[[nodiscard]] std::size_t Size() const; //Nodiscard means that the return value can NOT be discarded or else an error is returned.
		[[nodiscard]] bool IsEmpty();

		[[nodiscard]] T& Front();
		[[nodiscard]] const T& Front() const;
		[[nodiscard]] T& Back();
		[[nodiscard]] const T& Back() const;

		[[nodiscard]] void PushFront(const T& newValue);
		[[nodiscard]] void PopFront();
		Iterator PushBack(const T& newValue);
		Iterator PushBack(T&& newValue);
		[[nodiscard]] void PopBack();
		[[nodiscard]] void Clear();

		/// <summary>
		/// Returns an Iterator object that references the node at the front of the SList.
		/// </summary>
		[[nodiscard]] Iterator begin(); //Returns iterator to the beginning
		/// <summary>
		/// Returns an Iterator object that references the node one past the end of the SList.
		/// </summary>
		[[nodiscard]] Iterator end(); //Returns iterator to the end
		/// <summary>
		/// A constant function that returns a ConstIterator object that references the node at the front of the SList.
		/// </summary>
		[[nodiscard]] ConstIterator begin() const; //Returns ConstIterator to the beginning
		/// <summary>
		/// A constant function that returns a ConstIterator object that references the node one past the end of the SList.
		/// </summary>
		[[nodiscard]] ConstIterator end() const; //Returns ConstIterator to the end
		/// <summary>
		/// A constant function that returns a ConstIterator object that references the node at the front of the SList
		/// </summary>
		[[nodiscard]] ConstIterator CBegin() const;
		/// <summary>
		/// A constant function that returns a ConstIterator object that references the node at the front of the SList.
		/// </summary>
		[[nodiscard]] ConstIterator CEnd() const;
		/// <summary>
		/// A function that inserts a node with a user supplied value of the SList's type directly after a supplied iterator. Used to insder new data members at areas besides the back and front of the SList.
		/// </summary>
		/// <param name="newValue">The value to be held by the new data member.</param>
		/// <param name="iterator">The iterator that the new data member will be inserted after.</param>
		void InsertAfter(const T& newValue, Iterator iterator);
		/// <summary>
		/// A function that searches for a node that has the user-entered data value. If it exists in the SList, an iterator referencing it is returned.
		/// </summary>
		/// <param name="newValue">The value being searched for in the SList</param>
		/// <returns>An iterator that refers to nullptr if no match was found, or the first node encountered with the specified value.</returns>
		[[nodiscard]] Iterator Find(const T& newValue);
		/// <summary>
		/// A function that searches for a node that has the user-entered data value. If it exists in the SList, a ConstIterator referencing it is returned.
		/// </summary>
		/// <param name="newValue">The value being searched for in the SList</param>
		/// <returns>A ConstIterator that refers to nullptr if no match was found, or the first node encountered with the specified value.</returns>
		[[nodiscard]] ConstIterator Find(const T& newValue) const;
		/// <summary>
		/// Removes the node associated with the Iterator specified as an argument from the SList, if it exists in the SList. Used to remove nodes from places besides the front and back of the SList.
		/// </summary>
		/// <param name="position">A pass-by-reference Iterator that references the node the user wishes to remove from the SList.</param>
		///	<returns>A boolean value of True if the node was removed, or False if the node could not be found.</returns>
		bool Remove(const Iterator& position);
		/// <summary>
		/// Removes the node associated with the SList type T pointer value specified as an argument from the SList, if it exists in the SList. Used to remove nodes from places besides the front and back of the SList.
		/// </summary>
		/// <param name="value">The value carried by the node that the user wishes to remove.</param>
		/// <returns>A boolean value of True if the node was removed, or False if the node could not be found.</returns>
		bool Remove(const T* value);
	};
}

#include "SList.inl"