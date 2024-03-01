#include "attributes.hpp"



uintptr_t CCSPlayerController_Class::getListEntry() {
	listEntry = MemMan.read_memory<uintptr_t>(entityList + (0x8 * (id & 0x7FFF) >> 9) + 0x10);
	return listEntry;
}

uintptr_t CCSPlayerController_Class::getController() {
	value = MemMan.read_memory<uintptr_t>(listEntry + 0x78 * (id & 0x1FF));
	return value;
}

int CCSPlayerController_Class::getPawnHealth() {
	pawnHealth = MemMan.read_memory<int>(value + CCSPlayerController::m_iPawnHealth);
	return pawnHealth;
}

std::uint32_t CCSPlayerController_Class::getC_CSPlayerPawn() {
	C_CSPlayerPawn_ = MemMan.read_memory<std::uint32_t>(value + CCSPlayerController::m_hPlayerPawn);
	return C_CSPlayerPawn_;
}

uintptr_t CCSPlayerController_Class::getPawnTeam() {
	pawnTeam = MemMan.read_memory<uintptr_t>(value + C_BaseEntity::m_iTeamNum);
	return pawnTeam;
}

std::string CCSPlayerController_Class::getPawnName() {
	pawnNameAddress = MemMan.read_memory<uintptr_t>(value + CCSPlayerController::m_sSanitizedPlayerName);
	if (pawnNameAddress) {
		std::string buf = MemMan.read_memory<std::string>(pawnNameAddress);
		pawnName = buf;
	}
	else {
		pawnName = "Unknown";
	}
	return pawnName;
}



uintptr_t C_CSPlayerPawn_Class::getListEntry() {
	listEntry = MemMan.read_memory<uintptr_t>(entityList + 0x8 * ((value & 0x7FFF) >> 9) + 0x10);
	return listEntry;
}

uintptr_t C_CSPlayerPawn_Class::getPlayerPawn() {
	playerPawn = MemMan.read_memory<uintptr_t>(listEntry + 0x78 * (value & 0x1FF));
	return playerPawn;
}

uintptr_t C_CSPlayerPawn_Class::getPlayerPawnByCrossHairID(int crossHairEntity) {
	uintptr_t crosshairEntityEntry = MemMan.read_memory<uintptr_t>(entityList + 0x8 * (crossHairEntity >> 9) + 0x10);
	playerPawn = MemMan.read_memory<uintptr_t>(crosshairEntityEntry + 0x78 * (crossHairEntity & 0x1FF));
	return playerPawn;
}

Vector3 C_CSPlayerPawn_Class::getOrigin() {
	origin = MemMan.read_memory<Vector3>(playerPawn + C_BasePlayerPawn::m_vOldOrigin);
	return origin;
}

Vector3 C_CSPlayerPawn_Class::getCameraPos() {
	cameraPos = MemMan.read_memory<Vector3>(playerPawn + C_CSPlayerPawnBase::m_vecLastClipCameraPos);
	return cameraPos;
}

uintptr_t C_CSPlayerPawn_Class::getCGameSceneNode() {
	CGameSceneNode = MemMan.read_memory<uintptr_t>(playerPawn + C_BaseEntity::m_pGameSceneNode);
	return CGameSceneNode;
}

Vector3 C_CSPlayerPawn_Class::getViewAngles() {
	viewAngles = MemMan.read_memory<Vector3>(playerPawn + C_CSPlayerPawnBase::m_angEyeAngles);
	return viewAngles;
}

Vector3 C_CSPlayerPawn_Class::getPosition() {
	position = MemMan.read_memory<Vector3>(playerPawn + CBaseAnimGraph::m_vLastSlopeCheckPos);
	return position;
}

uint16_t C_CSPlayerPawn_Class::getWeaponID() {
	C_CSWeaponBase = MemMan.read_memory<uint64_t>(playerPawn + C_CSPlayerPawnBase::m_pClippingWeapon);
	weaponID = MemMan.read_memory<uint16_t>(C_CSWeaponBase + C_EconItemView::m_iItemDefinitionIndex + C_AttributeContainer::m_Item + C_EconEntity::m_AttributeManager);
	return weaponID;
}


int C_CSPlayerPawn_Class::getPawnHealth() {
	pawnHealth = MemMan.read_memory<int>(playerPawn + C_BaseEntity::m_iHealth);
	return pawnHealth;
}

uintptr_t C_CSPlayerPawn_Class::getPawnTeam() {
	pawnTeam = MemMan.read_memory<uintptr_t>(value + C_BaseEntity::m_iTeamNum);
	return pawnTeam;
}

int C_CSPlayerPawn_Class::getEntitySpotted() {
	spotted = MemMan.read_memory<DWORD_PTR>(playerPawn + C_CSPlayerPawnBase::m_entitySpottedState + EntitySpottedState_t::m_bSpottedByMask);
	return spotted;
}

int C_CSPlayerPawn_Class::getOwner() {
	owner = MemMan.read_memory<DWORD_PTR>(playerPawn + C_BaseEntity::m_hOwnerEntity);
	return owner;
}




uintptr_t LocalPlayer::getPlayerPawn() {
	playerPawn = MemMan.read_memory<uintptr_t>(base + client_dll::dwLocalPlayerPawn);
	return playerPawn;
}

uintptr_t LocalPlayer::getTeam() {
	team = MemMan.read_memory<uintptr_t>(localPlayer + C_BaseEntity::m_iTeamNum);
	return team;
}

Vector3 LocalPlayer::getCameraPos() {
	cameraPos = MemMan.read_memory<Vector3>(playerPawn + C_CSPlayerPawnBase::m_vecLastClipCameraPos);
	return cameraPos;
}

Vector3 LocalPlayer::getViewAngles() {
	viewAngles = MemMan.read_memory<Vector3>(playerPawn + C_BasePlayerPawn::v_angle);
	return viewAngles;
}

Vector3 LocalPlayer::getPosition() {
	position = MemMan.read_memory<Vector3>(playerPawn + CBaseAnimGraph::m_vLastSlopeCheckPos);
	return position;
}

Vector3 LocalPlayer::getOrigin() {
	origin = MemMan.read_memory<Vector3>(playerPawn + C_BasePlayerPawn::m_vOldOrigin);
	return origin;
}

int LocalPlayer::getFlags() {
	flags = MemMan.read_memory<int>(playerPawn + C_BaseEntity::m_fFlags);
	return flags;
}

C_UTL_VECTOR LocalPlayer::getAimPunchCache() {
	aimPunchCache = MemMan.read_memory<C_UTL_VECTOR>(playerPawn + C_CSPlayerPawn::m_aimPunchCache);
	return aimPunchCache;
}

Vector2 LocalPlayer::getAimPunchAngle() {
	aimPunchAngle = MemMan.read_memory<Vector2>(playerPawn + C_CSPlayerPawn::m_aimPunchAngle);
	return aimPunchAngle;
}

int LocalPlayer::getShotsFired() {
	shotsFired = MemMan.read_memory<int>(playerPawn + C_CSPlayerPawnBase::m_iShotsFired);
	return shotsFired;
}

void LocalPlayer::noFlash() {
	MemMan.write_memory<float>(playerPawn + C_CSPlayerPawnBase::m_flFlashDuration, 0.f);
}

int LocalPlayer::getEntitySpotted() {
	spotted = MemMan.read_memory<DWORD_PTR>(playerPawn + C_CSPlayerPawnBase::m_entitySpottedState + EntitySpottedState_t::m_bSpottedByMask);
	return spotted;
}

bool LocalPlayer::getIsScoped() {
	isScoped = MemMan.read_memory<DWORD_PTR>(playerPawn + C_CSPlayerPawnBase::m_bIsScoped);
	return isScoped;
}



uintptr_t CGameSceneNode_Class::getBoneArray() {
	boneArray = MemMan.read_memory<uintptr_t>(value + CSkeletonInstance::m_modelState + CGameSceneNode::m_vecOrigin);
	return boneArray;
}

Vector3 CGameSceneNode_Class::getOrigin() {
	origin = MemMan.read_memory<Vector3>(value + CGameSceneNode::m_vecAbsOrigin);
	return origin;
}



bool SharedFunctions::spottedCheck(C_CSPlayerPawn_Class C_CSPlayerPawn, LocalPlayer localPlayer) {
	if (C_CSPlayerPawn.getEntitySpotted() & (1 << (localPlayer.playerPawn)) || localPlayer.getEntitySpotted() & (1 << (C_CSPlayerPawn.playerPawn))) return 1;
	return 0;
}

bool SharedFunctions::inGame(DWORD_PTR base) {
	uintptr_t gameRules = MemMan.read_memory<uintptr_t>(base + client_dll::dwGameRules);

	bool warmup = MemMan.read_memory<bool>(gameRules + C_CSGameRules::m_bWarmupPeriod);
	bool match = MemMan.read_memory<bool>(gameRules + C_CSGameRules::m_bHasMatchStarted);
	bool freeze = MemMan.read_memory<bool>(gameRules + C_CSGameRules::m_bFreezePeriod);

	return match;
}