#pragma once
#include "aimbot.h"
namespace misc {

	inline namespace sharedData {
		inline int bhopInAir = (1 << 0);
	};

	void bunnyHop(DWORD_PTR base, int flags);
}