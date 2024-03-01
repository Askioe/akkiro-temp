#include "aimbot.h"

void aim::aimBot(LocalPlayer localPlayer, Vector3 baseViewAngles, DWORD_PTR baseViewAnglesAddy, uintptr_t boneArray) {
	Vector3 aimPos;
	Vector3 newAngle;
	Vector3 angle;

	aimPos = MemMan.read_memory<Vector3>(boneArray + 6 * 32);
	angle = CalculateAngle(localPlayer.cameraPos, aimPos, localPlayer.viewAngles);
	newAngle = calculateBestAngle(angle, 2.5);
	newAngle = clampAngles(newAngle);

	newAngle.x = newAngle.x / CGlobals::Smoothing;
	newAngle.y = newAngle.y / CGlobals::Smoothing;

	if (newAngle.IsZero()) {
		lockedPlayer = 0;
		return;
	}

	if (CGlobals::Aimbot) {
		if (GetAsyncKeyState(VK_TAB)) {
			MemMan.write_memory<Vector3>(baseViewAnglesAddy, baseViewAngles + newAngle);
		}
	}
	else {
		MemMan.write_memory<Vector3>(baseViewAnglesAddy, baseViewAngles + newAngle);
	}
}

void aim::recoilControl(LocalPlayer localPlayer, DWORD_PTR baseViewAnglesAddy) {
	localPlayer.getAimPunchCache();
	localPlayer.getViewAngles();

	static Vector3 oldPunch;
	Vector3 aimPunchAngle = MemMan.read_memory<Vector3>(localPlayer.aimPunchCache.data + (localPlayer.aimPunchCache.count - 1) * sizeof(Vector3));

	if (localPlayer.getShotsFired() > 1) {

		Vector3 recoilVector = {
			localPlayer.viewAngles.x + oldPunch.x - aimPunchAngle.x * 2.f,
			localPlayer.viewAngles.y + oldPunch.y - aimPunchAngle.y * 2.f
		};
		recoilVector = clampAngles(recoilVector);

		MemMan.write_memory<Vector3>(baseViewAnglesAddy, recoilVector);
	}
	oldPunch.x = aimPunchAngle.x * 2.f;
	oldPunch.y = aimPunchAngle.y * 2.f;
}


void aim::triggerBot(LocalPlayer localPlayer, DWORD_PTR base) {
	int crossHairEntity = MemMan.read_memory<int>(localPlayer.getPlayerPawn() + C_CSPlayerPawnBase::m_iIDEntIndex);
	if (!crossHairEntity) return;

	C_CSPlayerPawn_Class crossHairPawn(base);
	CCSPlayerController_Class crossHairEntityController(base);

	crossHairPawn.getPlayerPawnByCrossHairID(crossHairEntity);
	crossHairEntityController.value = crossHairPawn.playerPawn;

	bool isValidEntity = (crossHairEntity != -1 && crossHairPawn.getPawnHealth() > 0 && crossHairPawn.getPawnHealth() <= 100 && crossHairEntityController.getPawnTeam() != localPlayer.getTeam());

	if (CGlobals::Triggerbot) {
		if (GetAsyncKeyState(0x51)) {
			if (isValidEntity) {
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			};
		}
	}
	else {
		if (isValidEntity) {
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		};
	}
}