#include "RE/Condition.h"

#undef min
#undef max

#include "skse64_common/Relocation.h"  // RelocAddr
#include "skse64/GameForms.h"  // BGSPerk
#include "skse64/GameRTTI.h"  // DYNAMIC_CAST

#include <vector>  // vector
#include <utility>  // pair

#include "RE/Offsets.h"


namespace RE
{
	bool Condition::Node::Run(Visitor& a_visitor)
	{
		typedef bool _Run_t(Node* a_this, Visitor& a_visitor);
		static RelocAddr<_Run_t*> _Run(CONDITION_NODE_RUN);
		return _Run(this, a_visitor);
	}


	bool Condition::Run(TESObjectREFR* a_perkOwner, TESObjectREFR* a_target)
	{
		TESObjectREFR* runTarget = 0;
		std::vector<std::pair<bool, bool>> solutions;
		RunOn runOn = kRunOn_Target;
		Node* nodeStart = 0;
		TESObjectREFR* subject = 0;
		while (runOn) {
			switch (runOn) {
			case kRunOn_Target:
				runOn = kRunOn_PerkOwner;
				nodeStart = targetNodes;
				subject = a_target;
				break;
			case kRunOn_PerkOwner:
				runOn = kRunOn_None;
				nodeStart = perkOwnerNodes;
				subject = a_perkOwner;
				break;
			case kRunOn_None:
			default:
				break;
			}

			for (Node* node = nodeStart; node; node = node->next) {
				bool isOR = node->comparisonFlags.isOR;
				Visitor visitor(subject, 0);
				bool success = node->Run(visitor);
				solutions.emplace_back(isOR, success);
			}
		}

		UInt32 andCount = 0;
		UInt32 andTrue = 0;
		UInt32 orCount = 0;
		UInt32 orTrue = 0;
		for (auto& solution : solutions) {
			if (solution.first) {
				++orCount;
				orTrue += solution.second ? 1 : 0;
			} else {
				++andCount;
				andTrue += solution.second ? 1 : 0;
			}
		}

		bool andResult = andCount == andTrue;
		bool orResult = orCount ? orTrue > 0 : true;
		return andResult && orResult;
	}


	bool Condition::Match(TESObjectREFR* a_perkOwner, TESObjectREFR* a_target)
	{
		typedef bool _Match_t(Condition* a_this, TESObjectREFR* a_perkOwner, TESObjectREFR* a_target);
		static RelocAddr<_Match_t*> _Match(CONDITION_MATCH);
		return _Match(this, a_perkOwner, a_target);
	}
}
