#include "OperateReactionAttributed.h"
#include "pch.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(OperateReactionAttributed);

	OperateReactionAttributed::OperateReactionAttributed() :
		ReactionAttributed(TypeIdClass())
	{
		Subtype[0] = "Operate";
	}

	void OperateReactionAttributed::Update(const GameTime& currentTime)
	{
		auto stepValue = Find("Change");
		auto indexValue = Find("ArrayPosition");
		auto targetValue = Find("Focus");
		auto actions = Find("Actions");

		if (stepValue != nullptr && indexValue != nullptr && targetValue != nullptr && actions != nullptr)
		{
			for (size_t i = 0; i < actions->Size(); i++)
			{
				auto& currentValue = (*actions)[i];

				for (size_t j = 0; j < currentValue.Size(); j++)
				{
					auto& currentAction = currentValue.At(j).GetScope();
					auto step = currentAction->Find("Step");
					if (step == nullptr)
					{
						step = currentAction->Find("Multiplier");
						if (step == nullptr)
						{
							step = currentAction->Find("Divisor");
						}
					}
					auto index = currentAction->Find("Index");
					auto target = currentAction->Find("Target");
					if (step != nullptr && index != nullptr && target != nullptr)
					{
						step->SetInt(stepValue->GetInt());
						index->SetInt(indexValue->GetInt());
						target->SetString(targetValue->GetString());
					}
				}
			}
		}
		ActionList::Update(currentTime);
	}

	Vector<Signature> OperateReactionAttributed::Signatures()
	{
		return ReactionAttributed::Signatures();
	}
}