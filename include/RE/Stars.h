#pragma once

#include "RE/SkyObject.h"  // SkyObject


namespace RE
{
	class NiNode;


	class Stars : public SkyObject
	{
	public:
		virtual ~Stars();					// 00

		// override (SkyObject)
		virtual void Unk_03(void) override;	// 03


		// members
		NiNode*	unk10;	// 10
		UInt64	unk18;	// 18
	};
	STATIC_ASSERT(sizeof(Stars) == 0x20);
}