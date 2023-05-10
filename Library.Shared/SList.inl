#include "SList.h"
namespace FieaGameEngine
{
	template<typename T>

	inline SList<T>::Iterator::Iterator(const SList<T>*container, Node * nodeValue)
		: Owner{ container }, StoredValue{ nodeValue }
	{
	}

	template<typename T>
	typename bool SList<T>::Iterator::operator!=(Iterator comparedOperator) const //Not equal to operator for Iterator class
	{
		if (Owner == comparedOperator.Owner)
		{
			if (StoredValue == comparedOperator.StoredValue)
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	typename bool SList<T>::Iterator::operator==(Iterator comparedOperator) const //Equal to operator for iterator class
	{
		if (Owner == comparedOperator.Owner)
		{
			if (StoredValue == comparedOperator.StoredValue) //Compares position and owner (list and node) addresses to check for equality
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator++() //Increment operator for Iterator, changes pointer to next in list. Postfixes the operator.
	{
		if (StoredValue != nullptr)
		{
			StoredValue = StoredValue->next;
		}
		return *this;
	}

	template<typename T>
	typename inline SList<T>::Iterator SList<T>::Iterator::operator++(int32_t) //Increment operator for iterator, changes pointer to next in list. Prefixes the operator.
	{
		Iterator iterator = *this;
		operator++();
		return iterator;
	}

	template<typename T>
	inline T& SList<T>::Iterator::operator*() const //Pointer operator for iterator, supplies address reference
	{
		if (StoredValue == nullptr)
		{
			//return T();
			throw std::runtime_error("Iterator value is nullptr! Can not dereference.");
		}
		return StoredValue->value;
	}

	template<typename T>
	inline SList<T>::ConstIterator::ConstIterator(const SList<T>* container, Node* nodeValue)
		: Owner{ container }, StoredValue{ nodeValue }
	{
	}

	template<typename T>
	inline SList<T>::ConstIterator::ConstIterator(const SList<T>::Iterator& convertedIterator) //Type cast constructor
		: Owner{ convertedIterator.Owner }, StoredValue{ convertedIterator.StoredValue }
	{
	}

	template<typename T>
	typename inline bool SList<T>::ConstIterator::operator!=(ConstIterator comparedOperator) const//Not equal to operator for ConstIterator
	{
		if (Owner == comparedOperator.Owner)
		{
			if (StoredValue == comparedOperator.StoredValue)
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	typename inline bool SList<T>::ConstIterator::operator==(ConstIterator comparedOperator) const
	{
		if (Owner == comparedOperator.Owner)
		{
			if (StoredValue == comparedOperator.StoredValue) //Compares position and owner (list and node) addresses to check for equality
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	typename inline SList<T>::ConstIterator& SList<T>::ConstIterator::operator++()
	{
		if (StoredValue != nullptr)
		{
			StoredValue = StoredValue->next; //Goes to next value if not nullptr
		}
		return *this;
	}

	template<typename T>
	typename inline SList<T>::ConstIterator SList<T>::ConstIterator::operator++(int32_t)
	{
		ConstIterator iterator = *this;
		operator++();
		return iterator;
	}

	template<typename T>
	inline const T& SList<T>::ConstIterator::operator*() const
	{
		if (StoredValue == nullptr)
		{
			throw std::runtime_error("Iterator value is nullptr! Can not dereference.");
		}
		return StoredValue->value;
	}

	template<typename T>
	inline SList<T>::Node::Node(const T& data, SList<T>::Node* newLink)
		:value(data), next(newLink)
	{
	}

	template<typename T>
	inline SList<T>::Node::Node(T&& data, SList<T>::Node* newLink)
		: value(std::move(data)), next(newLink)
	{
	}

	template <typename T>
	inline SList<T>::SList() //Default constructor
	{
		front = nullptr; //Initializes all associated SList variables
		back = nullptr;
		_size = size_t(0);
	}

	template <typename T> //Copy constructor
	inline SList<T>::SList(const SList<T> &copiedList)
	{
		_size = 0; //Size is initialized to 0 for the new list
		if (copiedList.front != nullptr) //Next, each value is pushed onto the back from the existing to the new SList.
		{
			Node* currentNode = copiedList.front;
			while (currentNode != nullptr)
			{
				PushBack(currentNode->value);
				currentNode = currentNode->next;
			}
		}
	}

	template <typename T> //Copy constructor
	inline SList<T>::SList(SList&& other) noexcept :
		front(other.front), back(other.back), _size(other._size)
	{
		other.front = nullptr;
		other.back = nullptr;
		other._size = 0;
	}

	template <typename T>
	inline SList<T>& SList<T>::operator=(const SList &copiedList) //Operator = override
	{
		if (this != &copiedList)
		{
			if (_size > 0)
			{
				Clear();
			}
			Node* currentNode = copiedList.front;
			while (currentNode != nullptr)
			{
				PushBack(currentNode->value);
				currentNode = currentNode->next;
			}
		}
		return *this;
	}

	template <typename T>
	inline SList<T>& SList<T>::operator=(SList&& other)
	{
		if (this != &other)
		{
			if (_size > 0)
			{
				Clear();
			}
			
			front = other.front;
			back = other.back;
			_size = other._size;

			other.front = nullptr;
			other.back = nullptr;
			other._size = 0;
		}
		return *this;
	}


	template <typename T>
	inline SList<T>::~SList() //Destructor
	{
		if (!IsEmpty()) //As long as the list is not fully emptied, the clear function is called to wipe it
		{
			Clear();
		}
	}

	template <typename T>
	inline std::size_t SList<T>::Size() const //Returns the documented size of the list
	{
		return _size;
	}

	template<typename T>
	inline bool SList<T>::IsEmpty() //Returns whether or not the list is currently empty
	{
		if (_size == 0)
		{
			return true;
		}
		return false;
	}

	template <typename T>
	inline T& SList<T>::Front() //Returns the value held in the node at the front of the list.
	{
		if (_size == 0)
		{
			throw std::runtime_error("List is empty."); //Throws exception if the list is empty and the user is attempting to access a member
		}
		return (front->value);
	}

	template <typename T>
	inline const T& SList<T>::Front() const //Returns the value held in the node at the front of the list as a constant.
	{
		if (_size == 0)
		{
			throw std::runtime_error("List is empty."); //Throws exception if the list is empty and the user is attempting to access a member
		}
		return (front->value);
	}

	template<typename T>
	inline T& SList<T>::Back()
	{
		if (_size == 0)
		{
			throw std::runtime_error("List is empty."); //Throws exception if the list is empty and the user is attempting to access a member
		}
		return (back->value);
	}

	template<typename T>
	inline const T& SList<T>::Back() const
	{
		if (_size == 0)
		{
			throw std::runtime_error("List is empty."); //Throws exception if the list is empty and the user is attempting to access a member
		}
		return (back->value);
	}

	template <typename T>
	inline void SList<T>::PushFront(const T& newValue)  //Pushes a new value onto the front of the list
	{
		if (_size == 0) //Checks if the list is empty, if so, setting back and front to the only node added to the list
		{
			front = new Node(newValue);
			back = front;
			(*front).value = newValue;
		}
		else //Otherwise, a new node is added with a next value for the previous front node
		{
			Node* placeholder = front;

			front = new Node(newValue);
			(*front).next = placeholder;
		}
		_size++;
	}

	template<typename T>
	inline void SList<T>::PopFront()
	{
		if (!IsEmpty()) //Checks if list is empty to start since this is illegal behavior
		{
			if (_size == size_t(1)) //If only one element remains, delete it to free memory and reset front and back
			{
				delete(front);
				front = nullptr;
				back = nullptr;
			}
			else //If more than one element remains, the old front is deleted and the new front is set from its next pointer
			{
				Node placeholder = std::move(*front);
				delete(front);
				front = placeholder.next;
			}
			_size--; //Decrement size of list
			return;
		}

		throw std::runtime_error("List is empty.");
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::PushBack(const T& newValue)
	{
		if (_size == size_t(0)) //Checks if the list is empty, if so, setting back and front to the only node added to the list
		{
			front = new Node(newValue);
			back = front;
			//(*front).value = newValue;
		}
		else //Otherwise, a new node is added with a next value for the previous front node
		{
			Node* placeholder = back;
			back = new Node(newValue);
			(*placeholder).next = back;
		}

		_size++;
		//Node(const T & data, SList<T>::Node * newLink = nullptr)
		//Node* newNode(newValue, back->next);
		Iterator newIterator(this, back);
		return(newIterator);
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::PushBack(T&& newValue)
	{
		if (_size == size_t(0)) //Checks if the list is empty, if so, setting back and front to the only node added to the list
		{
			front = new Node(std::move(newValue));
			back = front;
			//(*front).value = newValue;
		}
		else //Otherwise, a new node is added with a next value for the previous front node
		{
			Node* placeholder = back;
			back = new Node(std::move(newValue));
			(*placeholder).next = back;
		}

		_size++;
		//Node(const T & data, SList<T>::Node * newLink = nullptr)
		//Node* newNode(newValue, back->next);
		Iterator newIterator(this, back);
		return(newIterator);
	}

	template<typename T>
	inline void SList<T>::PopBack() //Pops an element off of the back of the array
	{
		if (IsEmpty()) //Starts by checking if list is empty, since this should return an error
		{
			throw std::runtime_error("List is empty.");
		}
		else
		{
			if (_size == 1) //Otherwise, if size is 1 , the remaining element is deleted.
			{
				if (front != nullptr)
				{
					delete(front);
				}
				front = nullptr;
				back = nullptr;
			}
			else //If size is greater than 1, the old back is removed and new one is chosen
			{
				Node* placeholder= front;

				while (placeholder->next != back)
				{
					placeholder = placeholder->next;
				}
				delete(placeholder->next);
				placeholder->next = nullptr;
				back = placeholder;
			}
			_size--;
		}
	}

	template<typename T>
	inline void SList<T>::Clear() //Clears the full SList and frees memory inside it
	{
	//	if (IsEmpty()) //If the list is already clear, an error is thrown
	//	{
			//throw std::runtime_error("List is empty.");
		//}
		if(!IsEmpty())
		{
			if (_size == 1) //If only one element remains, the last element is removed
			{
				delete(front);
				_size--;
			}
			else //Otherwise, elements are deleted starting at the front of the list and continuing to the back in order
			{
				Node* placeholder = front;
				while (front != back)
				{
					placeholder = front->next;
					delete(front);
					front = placeholder;
					_size--;
				}
				delete(back);
				_size--;
			}
			front = nullptr;
			back = nullptr;
		}
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::begin()
	{
		return Iterator(this, front);
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::end()
	{
		return Iterator(this, nullptr); //End is pointing one past the end of the list. This means that there is no data stored, but the list is still considered its owner.
	}

	template<typename T>
	typename SList<T>::ConstIterator SList<T>::begin() const
	{
		return ConstIterator(this, front);
	}

	template<typename T>
	typename SList<T>::ConstIterator SList<T>::end() const
	{
		return ConstIterator(this, nullptr); //End is pointing one past the end of the list. This means that there is no data stored, but the list is still considered its owner.
	}

	template<typename T>
	typename SList<T>::ConstIterator SList<T>::CBegin() const
	{
		return ConstIterator(this, front);
	}

	template<typename T>
	typename SList<T>::ConstIterator SList<T>::CEnd() const
	{
		return ConstIterator(this, nullptr); //End is pointing one past the end of the list. This means that there is no data stored, but the list is still considered its owner.
	}

	template<typename T>
	typename void SList<T>::InsertAfter(const T& newValue, Iterator iterator) //Destroy first thing that matches value
	{
		if (iterator.Owner != this)
		{
			throw std::runtime_error("Can not insert item after iterator for a different list.");
		}
		if (iterator.StoredValue == nullptr || iterator.StoredValue->next == nullptr) //If stored value or next are null we are at the end of the list
		{
			PushBack(newValue);
			return;
		}
		Node* newItem = new Node(newValue, (iterator.StoredValue->next));
		iterator.StoredValue->next = newItem;
		_size++;
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::Find(const T& newValue)
	{
		Iterator position;
		for (position = begin(); position != end(); ++position)
		{
			if (position.StoredValue->value == newValue)
			{
				return (position);
			}
		}
		return(position);
	}

	template<typename T>
	typename SList<T>::ConstIterator SList<T>::Find(const T& newValue) const
	{
		ConstIterator position;
		for (position = begin(); position != end(); ++position)
		{
			if (position.StoredValue->value == newValue)
			{
				return (position);
			}
		}
		return(position);
	}

	template<typename T>
	typename bool SList<T>::Remove(const T* value)
	{
		Iterator position = Find(*value);
		return(Remove(position));
	}

	template<typename T>
	typename bool SList<T>::Remove(const Iterator& position)
	{
		if (position.Owner != this)
		{
			throw std::runtime_error("Can not insert item after iterator for a different list.");
		}

		if (position.StoredValue == nullptr)
		{
			return false;
		}

		if (position.StoredValue->next == nullptr)
		{
			PopBack();
			return true;
		}
		if (position.StoredValue == begin().StoredValue)
		{
			PopFront();
			return true;
		}

		for (Iterator leftNode = begin(); leftNode != end(); leftNode++)
		{
			if (leftNode.StoredValue->next == position.StoredValue)
			{
				leftNode.StoredValue->next = position.StoredValue->next;
				delete(position.StoredValue);
				_size--;
				return true;
			}
		}
		return false;
	}

	//template<typename T>
	//typename bool SList<T>::Remove(const Iterator& position)
	//{
	//	if (position.Owner != this)
	//	{
	//		throw std::runtime_error("Can not insert item after iterator for a different list.");
	//	}

	//	bool found = false;
	//	if (position != end())
	//	{
	//		if (position.StoredValue == front)
	//		{
	//			PopFront();
	//		}
	//		if (position.StoredValue == back)
	//		{
	//			PopBack();
	//		}
	//		else
	//		{
	//			Node& node = *position.StoredValue;
	//			Node* next = position.StoredValue->next;
	//			node.value.~T();
	//			new(&position.StoredValue->value)T(std::move(next->value));
	//			position.StoredValue->next = next->next;
	//			delete next;

	//			if (position.StoredValue->next == nullptr)
	//			{
	//				back = position.StoredValue;
	//			}
	//			--_size;
	//		}

	//		found = true;
	//	}

	//	return found;
	//}
}