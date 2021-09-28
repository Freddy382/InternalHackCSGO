#include "player.h"
#include <Windows.h>
#include <iostream>
#include "offsets.h"
#include "vector.h"
#include "templates.h"

static uintptr_t gameModule = (uintptr_t)(GetModuleHandle("client.dll"));

Player* Player::Get(int index) {
	return (Player*)(*(uintptr_t*)(gameModule + dwEntityList + index * 0x10));
}

int Player::GetHealth() {
	return *(uintptr_t*)(this + m_iHealth);
}

int Player::GetTeam() {
	return *(uintptr_t*)(this + m_iTeamNum);
}

Vector3 Player::GetBones() {
	uintptr_t bones = *(uintptr_t*)(this + m_dwBoneMatrix);
	float x = *(float*)(bones + 0x30 * 8 + 0xC);
	float y = *(float*)(bones + 0x30 * 8 + 0x1C);
	float z = *(float*)(bones + 0x30 * 8 + 0x2C);

	Vector3 pos = Vector3(x, y, z);

	return pos;
}

