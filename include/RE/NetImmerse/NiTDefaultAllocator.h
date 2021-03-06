#pragma once

#include "RE/NetImmerse/NiTCollection.h"

#define NiTDefaultAllocator DFALL


namespace RE
{
	template <class T>
	class NiTDefaultAllocator
	{
	public:
		void* Allocate()
		{
			return NiMalloc(sizeof(T));
		}


		void Deallocate(void* a_ptr)
		{
			return NiFree(a_ptr);
		}
	};
}
