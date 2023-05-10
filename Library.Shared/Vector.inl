#include "Vector.h"
/// <summary>
/// The file specifying allowed operations and constructors for the Vector class, outlining each potential method to be used on vectors, iterators, and constiterators.
/// </summary>
namespace FieaGameEngine
{
	template<typename T>
	inline Vector<T>::Iterator::Iterator(Vector<T>& container, size_t indexValue)
		: Owner{ &container }, Index{indexValue}
	{
	}

	template<typename T>
	typename bool Vector<T>::Iterator::operator!=(const Iterator comparedIterator) const //Not equal to operator for Iterator class
	{
		return !(Index == comparedIterator.Index && (Owner == comparedIterator.Owner));
	}

	template<typename T>
	typename bool Vector<T>::Iterator::operator==(const Iterator comparedIterator) const //Equal to operator for Iterator class
	{
		return Index == comparedIterator.Index && (Owner == comparedIterator.Owner);
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++() //Increment operator for Iterator, changes pointer to next in Vector. Postfixes the operator.
	{
		if (Owner != nullptr)
		{
			if (Index < Owner->VectorSize)
			{
				Index++;
			}
		}
		return *this;
	}

	template<typename T>
	typename inline Vector<T>::Iterator Vector<T>::Iterator::operator++(int) //Increment operator for iterator, changes pointer to next in Vector. Prefixes the operator.
	{
		Iterator iterator = *this;
		operator++();
		return iterator;
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator--() //Decrement operator for iterator, changes pointer to previous in Vector. Postfixes the operator.
	{
		if (Index > 0)
		{
			Index--;
		}
		return *this;
	}

	template<typename T>
	typename inline Vector<T>::Iterator Vector<T>::Iterator::operator--(int) //Decrement operator for iterator, changes pointer to previous in Vector. Prefixes the operator.
	{
		Iterator iterator = *this;
		operator--();
		return iterator;
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator-=(size_t decrement)
	{
		if (Index > decrement)
		{
			Index -= decrement;
		}
		else
		{
			Index = 0;
		}
		return *this;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator-(size_t decrement)
	{
		Iterator* solution = this;
		if (Index > decrement)
		{
			solution->Index -= decrement;
		}
		else
		{
			solution->Index = 0;
		}
		return *solution;
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator+=(size_t increment)
	{
		if (Index + increment < Owner->Size())
		{
			Index += increment;
		}
		else
		{
			Index = Owner->Size();
		}
		return *this;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator+(size_t increment)
	{
		Iterator* solution = this;
		if (Index + increment < Owner->Size())
		{
			solution->Index += increment;
		}
		else
		{
			solution->Index = Owner->Size();
		}
		return *solution;
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator-=(Iterator decrement)
	{
		if (decrement.Owner != Owner)
		{
			throw std::runtime_error("Cannot subtract iterators from different vectors!");
		}
		if (Index > decrement.Index)
		{
			Index -= decrement.Index;
		}
		else
		{
			Index = 0;
		}
		return *this;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator-(Iterator& decrement)
	{
		if (decrement.Owner != Owner)
		{
			throw std::runtime_error("Cannot subtract iterators from different vectors!");
		}
		Iterator* solution = this;
		if (Index > decrement.Index)
		{
			solution->Index -= decrement.Index;
		}
		else
		{
			solution->Index = 0;
		}
		return *solution;
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator+=(Iterator increment)
	{
		if (increment.Owner != Owner)
		{
			throw std::runtime_error("Cannot add iterators from different vectors!");
		}
		if(Index + increment.Index < Owner->Size())
		{
			Index += increment.Index;
		}
		else
		{
			Index = Owner->Size();
		}
		return *this;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator+(Iterator& increment)
	{
		if (increment.Owner != Owner)
		{
			throw std::runtime_error("Cannot add iterators from different vectors!");
		}
		Iterator* solution = this;

		if (Index + increment.Index < Owner->Size())
		{
			solution->Index += increment.Index;
		}
		else
		{
			solution->Index = Owner->Size();
		}
		return *solution;
	}

	template<typename T>
	inline T& Vector<T>::Iterator::operator*() const
	{
		if (Owner == nullptr)
		{
			throw std::runtime_error("Owner value is nullptr! Can not dereference.");
		}
		if (Index >= Owner->VectorSize)
		{
			throw std::runtime_error("Iterator value is nullptr! Can not dereference.");
		}
		return *(Owner->VectorData + Index);
	}

	template<typename T>
	inline void Vector<T>::Iterator::operator=(const Iterator& copiedIterator)
	{
		Index = copiedIterator.Index;
		Owner = copiedIterator.Owner;
	}

	template<typename T>
	inline void Vector<T>::ConstIterator::operator=(const ConstIterator& copiedIterator)
	{
		Index = copiedIterator.Index;
		Owner = copiedIterator.Owner;
	}

	template<typename T>
	inline Vector<T>::ConstIterator::ConstIterator(Vector<T>* container, size_t indexValue)
		: Owner{ container }, Index{ indexValue }
	{
	}

	//template<typename T>
	//inline Vector<T>::ConstIterator::ConstIterator(const ConstIterator& copiedIterator) :
//		Index{ copiedIterator.Index }, Owner{ copiedIterator.Owner }
//	{
//	}

	template<typename T>
	typename bool Vector<T>::ConstIterator::operator!=(const ConstIterator comparedIterator) const //Not equal to operator for Iterator class
	{
		if (Index == comparedIterator.Index && (Owner == comparedIterator.Owner))
		{
			return false;
		}
		return true;
	}

	template<typename T>
	typename bool Vector<T>::ConstIterator::operator==(const ConstIterator comparedIterator) const //Equal to operator for Iterator class
	{
		if (Owner == comparedIterator.Owner && (Index == comparedIterator.Index))
		{
			return true;
		}
		return false;
	}

	template<typename T>
	typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator++() //Increment operator for Iterator, changes pointer to next in list. Postfixes the operator.
	{
		if (Index < Owner->VectorSize)
		{
			Index++;
		}
		return *this;
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++(int) //Increment operator for iterator, changes pointer to next in list. Prefixes the operator.
	{
		ConstIterator iterator = *this;
		operator++();
		return iterator;
	}

	template<typename T>
	typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator--()
	{
		if (Index > 0)
		{
			Index--;
		}
		return *this;
	}

	template<typename T>
	typename inline Vector<T>::ConstIterator Vector<T>::ConstIterator::operator--(int)
	{
		ConstIterator iterator = *this;
		operator--();
		return iterator;
	}

	template<typename T>
	typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator-=(size_t decrement)
	{
		if (Index > decrement)
		{
			Index -= decrement;
		}
		else
		{
			Index = 0;
		}
		return *this;
	}

	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator-(size_t decrement)
	{
		ConstIterator* solution = this;
		if (Index > decrement)
		{
			solution->Index -= decrement;
		}
		else
		{
			solution->Index = 0;
		}
		return *solution;
	}

	template<typename T>
	typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator+=(size_t increment)
	{
		if (Index + increment < Owner->Size())
		{
			Index += increment;
		}
		else
		{
			Index = Owner->Size();
		}
		return *this;
	}

	template<typename T>
	typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator-=(const ConstIterator decrement)
	{
		if (decrement.Owner != Owner)
		{
			throw std::runtime_error("Cannot subtract iterators from different vectors!");
		}
		if (Index > decrement.Index)
		{
			Index -= decrement.Index;
		}
		else
		{
			Index = 0;
		}
		return *this;
	}

	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator-(const ConstIterator& decrement)
	{
		if (decrement.Owner != Owner)
		{
			throw std::runtime_error("Cannot subtract iterators from different vectors!");
		}
		ConstIterator* solution = this;
		if (Index > decrement.Index)
		{
			solution->Index -= decrement.Index;
		}
		else
		{
			solution->Index = 0;
		}
		return *solution;
	}

	template<typename T>
	typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator+=(const ConstIterator increment) 
	{
		if (increment.Owner != Owner)
		{
			throw std::runtime_error("Cannot add iterators from different vectors!");
		}
		if (Index+increment.Index < Owner->Size())
		{
			Index += increment.Index;
		}
		else
		{
			Index = Owner->Size();
		}
		return *this;
	}

	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator+(size_t increment)
	{
		ConstIterator* solution = this;
		if (Index + increment < Owner->Size())
		{
			solution->Index += increment;
		}
		else
		{
			solution->Index = Owner->Size();
		}
		return *solution;
	}

	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator+(const ConstIterator& increment)
	{
		if (increment.Owner != Owner)
		{
			throw std::runtime_error("Cannot add iterators from different vectors!");
		}
		ConstIterator* solution = this;

		if (Index + increment.Index < Owner->Size())
		{
			solution->Index += increment.Index;
		}
		else
		{
			solution->Index = Owner->Size();
		}
		return *solution;
	}

	template<typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Vector<T>::Iterator& convertedIterator) //Type cast constructor
		: Owner{ convertedIterator.Owner }, Index{ convertedIterator.Index }
	{
	}

	template<typename T>
	inline const T& Vector<T>::ConstIterator::operator*() const
	{
		if (Owner == nullptr)
		{
			throw std::runtime_error("Owner value is nullptr! Can not dereference.");
		}
		if (Index >= Owner->VectorSize)
		{
			throw std::runtime_error("Iterator value is nullptr! Can not dereference.");
		}
		return *(Owner->VectorData + Index);
	}

	template<typename T>
	inline Vector<T>::Vector(Vector&& movingVector) noexcept //Move constructor
		: VectorSize(movingVector.VectorSize)
		, VectorCapacity(movingVector.VectorCapacity)
		, VectorData(movingVector.VectorData)
	{
		movingVector.VectorSize = 0;
		movingVector.VectorCapacity = 0;
		movingVector.VectorData = nullptr;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(Vector<T>&& movingVector) noexcept //Move assignment
	{
		if (this != &movingVector)
		{
			Clear();
			ShrinkToFit();
			VectorSize = movingVector.VectorSize;
			VectorCapacity = movingVector.VectorCapacity;
			VectorData = movingVector.VectorData;

			movingVector.VectorSize = 0;
			movingVector.VectorCapacity = 0;
			movingVector.VectorData = nullptr;
		}
		return *this;
	}

	template <typename T>
	inline Vector<T>::~Vector() //Destructor
	{
		Clear();
		ShrinkToFit();
	}

	template <typename T>
	inline Vector<T>::Vector(const Vector& copiedVector) //Copy constructor doesn't need checks to make sure the vectors aren't equal, as the left hand side vector is always default, empty array.
	{
		for (size_t i = 0; i < copiedVector.VectorSize; i++)
		{
			PushBack(copiedVector.VectorData[i]);
		}
	}

	template <typename T>
	T& Vector<T>::operator[](const size_t index)
	{
		if (index >= VectorSize)
		{
			throw std::runtime_error("Index exceeds size of array!");
		}
		return(VectorData[index]);
	}

	template <typename T>
	T& Vector<T>::operator[](const size_t index) const
	{
		if (index >= VectorSize)
		{
			throw std::runtime_error("Index exceeds size of array!");
		}
		return(VectorData[index]);
	}

	template <typename T>
	void Vector<T>::operator=(const Vector& copiedVector)
	{
		if (this != &copiedVector)
		{
			if (VectorSize > 0)
			{
				Clear();
			}

			for (size_t i = 0; i < copiedVector.VectorSize; i++)
			{
				PushBack(copiedVector.VectorData[i]);
			}
		}
	}

	template <typename T>
	inline T& Vector<T>::At(size_t index)
	{
		if (index >= VectorSize)
		{
			throw std::runtime_error("Index exceeds size of array!");
		}
		return(VectorData[index]);
	}

	template <typename T>
	inline T& Vector<T>::At(size_t index) const
	{
		if (index >= VectorSize)
		{
			throw std::runtime_error("Index exceeds size of array!");
		}
		return(VectorData[index]);
	}

	template <typename T>
	inline void Vector<T>::PushBack(const T& newItem)
	{
		if (VectorSize == VectorCapacity)
		{
			Reserve(uint32_t(VectorCapacity+1));
		}
		new(VectorData + VectorSize)T(newItem);
		VectorSize++;
	}

	template <typename T>
	inline void Vector<T>::PushBack(T&& newItem)
	{
		if (VectorSize == VectorCapacity)
		{
			Reserve(uint32_t(VectorCapacity + 1));
		}
		new(VectorData + VectorSize)T(std::move(newItem));
		VectorSize++;
	}

	template <typename T>
	inline void Vector<T>::PopBack()
	{
		if (VectorSize > 0)
		{
			(VectorData[VectorSize - 1]).~T();
			VectorSize--;
		}
	}

	template <typename T>
	inline bool Vector<T>::IsEmpty() const
	{
		return(VectorSize == 0);
	}

	template <typename T>
	inline T& Vector<T>::Front()
	{
		if (VectorSize == 0)
		{
			throw std::runtime_error("Front value is null! Cannot dereference.");
		}
		return VectorData[0];
	}

	template <typename T>
	inline T& Vector<T>::Front() const
	{
		if (VectorSize == 0)
		{
			throw std::runtime_error("Front value is null! Cannot dereference.");
		}
		return VectorData[0];
	}

	template <typename T>
	inline T& Vector<T>::Back()
	{
		if (VectorSize == 0)
		{
			throw std::runtime_error("Back value is null! Cannot dereference.");
		}
		return VectorData[VectorSize-1];
	}

	template <typename T>
	inline T& Vector<T>::Back() const
	{
		if (VectorSize == 0)
		{
			throw std::runtime_error("Back value is null! Cannot dereference.");
		}
		return VectorData[VectorSize - 1];
	}

	template<typename T>
	size_t Vector<T>::Size() const
	{
		return VectorSize;
	}

	template<typename T>
	inline size_t Vector<T>::Capacity() const
	{
		return VectorCapacity;
	}

	template<typename T>
	void Vector<T>::Reserve(size_t elements)
	{
		if (elements > std::numeric_limits<size_t>::max())
		{
			throw std::runtime_error("Cannot allocate: Number of elements exceeds allowed size.");
		}

		if (elements > VectorCapacity)
		{
			T* newData;
			newData = reinterpret_cast<T*>(realloc(VectorData, elements * sizeof(T)));
			assert(newData != nullptr);
			VectorData = newData;
			VectorCapacity = elements;
		}
	}

	template<typename T>
	void Vector<T>::ShrinkToFit()
	{
		if (VectorSize == 0)
		{
			free(VectorData);
			VectorSize = 0;
			VectorCapacity = 0;
			VectorData = nullptr;
		}
		else if(VectorSize != VectorCapacity)
		{
			T* newData = reinterpret_cast<T*>(realloc(VectorData, VectorSize * sizeof(T)));
			assert(newData != nullptr);
			VectorData = newData;
			VectorCapacity = VectorSize;
		}
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const T& targetValue) const
	{
		Iterator position;
		for (position = begin(); position != end(); ++position)
		{
			if (*position == targetValue)
			{
				return position;
			}
		}
		return position;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const T& targetValue)
	{
		Iterator position;
		for (position = begin(); position != end(); ++position)
		{
			if (*position == targetValue)
			{
				return position;
			}
		}
		return position;
	}

	template<typename T>
	void Vector<T>::Clear()
	{
		for (Iterator traverser = begin(); traverser != end(); traverser++)
		{
			(VectorData + traverser.Index)->~T();
		}
		VectorSize = 0;
	}

	template<typename T>
	bool Vector<T>::Remove(const T& elementRemoved)
	{
		return Remove(Find(elementRemoved));
	}
	template<typename T>
	typename bool Vector<T>::Remove(const Iterator& position)
	{
		if (position.Owner != this)
		{
			throw std::runtime_error("Can not remove iterator value from vector it's not associated to!");
		}

		if (position.Index >= VectorSize)
		{
			return false;
		}
		(VectorData + position.Index)->~T(); //Delete the element in question using its index and start of vector
		if (position.Index < VectorSize - 1) //If moved from the middle of the array, moves any elements following it back to fully fill array
		{
			memmove((VectorData + position.Index), (VectorData + position.Index + 1), (sizeof(T) * (VectorSize - position.Index)));
		}
		VectorSize--;
		return true;
	}

	template<typename T>
	typename bool Vector<T>::Remove(const Iterator& start, const Iterator& end) //Removes all elements between start and end, inclusive
	{
		if (start.Owner != this || end.Owner != this)
		{
			throw std::runtime_error("Can not remove iterator value range tied to different vector!");
		}

		if (start.Index >= VectorSize || end.Index >= VectorSize || start.Index > end.Index)
		{
			return false;
		}
		for (size_t i = start.Index; i <= end.Index; i++)
		{
			(VectorData + i)->~T(); //Delete the element in question using its index and start of vector
		}
		if (end.Index < (VectorSize - 1)) //If moved from the middle of the array, moves any elements following it back to fully fill array
		{
			memmove((VectorData + start.Index), (VectorData + end.Index + 1), (sizeof(T) * (VectorSize - end.Index)));
		}
		VectorSize-= (end.Index - start.Index +1);
		return true;
	}

	template<typename T>
	typename bool Vector<T>::Remove(const ConstIterator& start, const ConstIterator& end) //Removes all elements between start and end, inclusive
	{
		if (start.Owner != this || end.Owner != this)
		{
			throw std::runtime_error("Can not remove iterator value range tied to different vector!");
		}

		if (start.Index >= VectorSize || end.Index >= VectorSize || start.Index > end.Index)
		{
			return false;
		}
		for (size_t i = start.Index; i <= end.Index; i++)
		{
			(VectorData + i)->~T(); //Delete the element in question using its index and start of vector
		}
		if (end.Index < (VectorSize - 1)) //If moved from the middle of the array, moves any elements following it back to fully fill array
		{
			memmove((VectorData + start.Index), (VectorData + end.Index + 1), (sizeof(T) * (VectorSize - end.Index)));
		}
		VectorSize -= (end.Index - start.Index + 1);
		return true;
	}

	template<typename T>
	typename bool Vector<T>::Remove(const ConstIterator& position)
	{
		if (position.Owner != this)
		{
			throw std::runtime_error("Cannot remove item associated to constiterator from vector it doesnt belong to!");
		}

		if (position.Index >= VectorSize)
		{
			return false;
		}

		(VectorData + position.Index)->~T();
		if (position.Index < VectorSize - 1)
		{
			memmove((VectorData + position.Index), (VectorData + position.Index + 1), (sizeof(T) * (VectorSize - position.Index)));
		}
		VectorSize--;
		return true;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::begin()
	{
		return Iterator(*this, 0);
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::end()
	{
		return Iterator(*this, VectorSize); //End is pointing one past the end of the list. This means that there is no data stored, but the list is still considered its owner.
	}

	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::cbegin()
	{
		return ConstIterator(this, 0);
	}

	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::cend()
	{
		return ConstIterator(this, VectorSize);//End is pointing one past the end of the list. This means that there is no data stored, but the list is still considered its owner.
	}
}