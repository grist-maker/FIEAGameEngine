#include "IJsonParseHelper.h"
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(IJsonParseHelper);

	void IJsonParseHelper::Initialize()
	{

	}

	std::shared_ptr<IJsonParseHelper> IJsonParseHelper::Create() const
	{
		std::shared_ptr<IJsonParseHelper> newHelp(nullptr);
		return newHelp;
	}

	void IJsonParseHelper::Cleanup()
	{

	}
}