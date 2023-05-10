#pragma once
#include "SList.h"

namespace FieaGameEngine
{
	template <typename T>
	class Stack final
	{
	public:
		using sizeType = std::size_t;
		using valueType = T;
		using reference = valueType&;
		using constReference = const valueType&;
		using rvalueReference = valueType&&;

		template <typename... Args>
		void Emplace(Args&&... args);
		void Push(constReference value);
		void Push(rvalueReference value);
		void Pop();
		[[nodiscard]] reference Top();
		[[nodiscard]] constReference Top() const;

		[[nodiscard]] sizeType Size() const;
		[[nodiscard]] bool IsEmpty() const;

		void Clear();

	private:
		SList<valueType> List;
	};
}
#include "Stack.inl"