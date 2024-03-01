#pragma once
#pragma warning (disable: 26495)
#include "memory.h"


struct C_UTL_VECTOR
{
	DWORD_PTR count = 0;
	DWORD_PTR data = 0;
};


static CMemory MemMan;



class CCSPlayerController_Class {
public:
	uintptr_t entityList;
	int id;

	CCSPlayerController_Class(uintptr_t base) {
		UpdateEntityList(base);
	}
	
	uintptr_t UpdateEntityList(uintptr_t base) {
		entityList = MemMan.read_memory<uintptr_t>(base + client_dll::dwEntityList);
		return entityList;
	}

	uintptr_t listEntry;
	uintptr_t getListEntry();

	uintptr_t value;
	uintptr_t getController();

	int pawnHealth;
	int getPawnHealth();

	uintptr_t pawnTeam;
	uintptr_t getPawnTeam();

	uintptr_t pawnNameAddress;
	std::string pawnName;
	std::string getPawnName();

	// C_CSPlayerPawn
	std::uint32_t C_CSPlayerPawn_;
	std::uint32_t getC_CSPlayerPawn();
};


class C_CSPlayerPawn_Class {
public:
	std::uint32_t value;
	uintptr_t entityList;

	C_CSPlayerPawn_Class(uintptr_t base) {
		UpdateEntityList(base);
	}

	uintptr_t UpdateEntityList(uintptr_t base) {
		entityList = MemMan.read_memory<uintptr_t>(base + client_dll::dwEntityList);
		return entityList;
	}; 

	uintptr_t listEntry;
	uintptr_t getListEntry();

	uintptr_t playerPawn;
	uintptr_t getPlayerPawn();
	uintptr_t getPlayerPawnByCrossHairID(int crossHairEntity);

	Vector3 origin;
	Vector3 getOrigin();

	Vector3 cameraPos;
	Vector3 getCameraPos();

	Vector3 viewAngles;
	Vector3 getViewAngles();

	Vector3 position;
	Vector3 getPosition();

	int pawnHealth;
	int getPawnHealth();

	uintptr_t pawnTeam;
	uintptr_t getPawnTeam();

	uint64_t C_CSWeaponBase;
	uint16_t weaponID;
	std::string weaponName;
	uint16_t getWeaponID();

	int spotted;
	int getEntitySpotted();

	int owner;
	int getOwner();

	// CGameSceneNode
	uintptr_t CGameSceneNode;
	uintptr_t getCGameSceneNode();

};

class CGameSceneNode_Class {
public:
	uintptr_t value;

	uintptr_t boneArray;
	uintptr_t getBoneArray();

	Vector3 origin;
	Vector3 getOrigin();
};


class LocalPlayer {
public:
	uintptr_t localPlayer;
	uintptr_t base;

	LocalPlayer(uintptr_t baseAddy) {
		base = baseAddy;
		UpdateLocalPlayer();
	}

	uintptr_t UpdateLocalPlayer() {
		localPlayer = MemMan.read_memory<uintptr_t>(base + client_dll::dwLocalPlayerController);
		return localPlayer;
	}

	uintptr_t playerPawn;
	uintptr_t getPlayerPawn();

	uintptr_t team;
	uintptr_t getTeam();

	Vector3 cameraPos;
	Vector3 getCameraPos();

	Vector3 origin;
	Vector3 getOrigin();

	Vector3 viewAngles;
	Vector3 getViewAngles();

	Vector3 position;
	Vector3 getPosition();

	int flags;
	int getFlags();

	C_UTL_VECTOR aimPunchCache;
	C_UTL_VECTOR getAimPunchCache();

	Vector2 aimPunchAngle;
	Vector2 getAimPunchAngle();

	int shotsFired;
	int getShotsFired();

	void noFlash();

	int spotted;
	int getEntitySpotted();

	bool isScoped;
	bool getIsScoped();
};


// This is unrelated to all the other classes, but this is the most convenient way to share functions between features
class SharedFunctions {
public:
	static bool spottedCheck(C_CSPlayerPawn_Class C_CSPlayerPawn, LocalPlayer localPlayer);
	static bool inGame(DWORD_PTR base);
};