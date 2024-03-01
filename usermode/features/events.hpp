#include "misc.h"

static CCSPlayerController_Class		CCSPlayerController_Base(MemMan.client);
static C_CSPlayerPawn_Class			C_CSPlayerPawn_Base(MemMan.client);
static CGameSceneNode_Class			CGameSceneNode_Base;
static LocalPlayer				localPlayer(MemMan.client);

void MainLoop() {

	if (SharedFunctions::inGame(MemMan.client)) {
		view_matrix_t viewMatrix = MemMan.read_memory<view_matrix_t>(MemMan.client + client_dll::dwViewMatrix);
		Vector3 baseViewAngles = MemMan.read_memory<Vector3>(MemMan.client + client_dll::dwViewAngles);
		DWORD_PTR baseViewAnglesAddy = MemMan.client + client_dll::dwViewAngles;
		uintptr_t entityList = MemMan.read_memory<uintptr_t>(MemMan.client + client_dll::dwEntityList);

		if (CGlobals::RCS) aim::recoilControl(localPlayer, baseViewAnglesAddy);

		if (CGlobals::Bhop) misc::bunnyHop(MemMan.client, localPlayer.getFlags());

		// Flash
		if (CGlobals::NoFlash) localPlayer.noFlash();

		// Tigger
		if (CGlobals::Triggerbot) aim::triggerBot(localPlayer, MemMan.client);
	}
}

#if TRUE
#else
// Main loop
for (int i = 0; i < 64; i++) {

	// Player controller
	CCSPlayerController_Base.id = i;
	CCSPlayerController_Base.getListEntry();
	CCSPlayerController_Base.getController();
	if (CCSPlayerController_Base.value == 0) continue;
	CCSPlayerController_Base.getPawnName();

	// Player pawn
	C_CSPlayerPawn_Base.value = CCSPlayerController_Base.getC_CSPlayerPawn();
	C_CSPlayerPawn_Base.getListEntry();
	C_CSPlayerPawn_Base.getPlayerPawn();
	C_CSPlayerPawn_Base.getPawnHealth();

	// Checks
	if (aim::lockedPlayer == C_CSPlayerPawn_Base.playerPawn && C_CSPlayerPawn_Base.pawnHealth <= 0) aim::lockedPlayer = 0;
	if ((C_CSPlayerPawn_Base.pawnHealth <= 0 || C_CSPlayerPawn_Base.pawnHealth > 100) || localPlayer.getTeam() == C_CSPlayerPawn_Base.getPawnTeam()) continue;


	// Game scene node
	CGameSceneNode_Base.value = C_CSPlayerPawn_Base.getCGameSceneNode();

	// Aim
	if (CGlobals::Aimbot) {


		CGameSceneNode_Base.value = C_CSPlayerPawn_Base.getCGameSceneNode();
		CGameSceneNode_Base.getBoneArray();

		localPlayer.getCameraPos();
		localPlayer.getViewAngles();

		if (CGlobals::checkSpotted) {
			if (SharedFunctions::spottedCheck(C_CSPlayerPawn_Base, localPlayer)) {
				aim::aimBot(localPlayer, baseViewAngles, baseViewAnglesAddy, CGameSceneNode_Base.boneArray);
			}
		}
		else {
			aim::aimBot(localPlayer, baseViewAngles, baseViewAnglesAddy, CGameSceneNode_Base.boneArray);
		}
	}
}

#endif