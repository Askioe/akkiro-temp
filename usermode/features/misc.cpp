#include "misc.h"

void misc::bunnyHop(DWORD_PTR base, int flags) {
	if (GetAsyncKeyState(VK_SPACE) && flags & bhopInAir) {
		MemMan.write_memory<int>(base + client_dll::dwForceJump, 65537);
	}
	else {
		MemMan.write_memory<int>(base + client_dll::dwForceJump, 256);
	}
}