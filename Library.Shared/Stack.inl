#include "Stack.h"
namespace FieaGameEngine
{
	template<typename T>
	template <typename... Args>
	inline void Stack<T>::Emplace(Args&&... args)
	{
		List.PushFront(std::forward<Args>(args)...);
	}

	template <typename T>
	inline void Stack<T>::Push(constReference value)
	{
		List.PushFront(value);
	}

	template <typename T>
	inline void Stack<T>::Push(rvalueReference value)
	{
		List.PushFront(std::move(value));
	}

	template <typename T>
	inline void Stack<T>::Pop()
	{
		List.PopFront();
	}

	template <typename T>
	inline typename Stack<T>::reference Stack<T>::Top()
	{
		return List.Front();
	}

	template <typename T>
	inline typename Stack<T>::constReference Stack<T>::Top() const
	{
		return List.Front();
	}

	template <typename T>
	inline typename Stack<T>::sizeType Stack<T>::Size() const
	{
		return List.Size();
	}

	template <typename T>
	inline bool Stack<T>::IsEmpty() const
	{
		return List.Size() == 0;
	}

	template <typename T>
	inline void Stack<T>::Clear()
	{
		return List.Clear();
	}
}