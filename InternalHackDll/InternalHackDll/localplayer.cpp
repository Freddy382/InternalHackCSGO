#include "localplayer.h"
#include "vector.h"
#include <Windows.h>
#include <iostream>
#include "offsets.h"
#include <sstream>
#include <cstdint>
#include "templates.h"
#include "player.h"
#include "math.h"

static uintptr_t gameModule = (uintptr_t)(GetModuleHandle("client.dll"));
static uintptr_t engineModule = *(uintptr_t*)((uintptr_t)GetModuleHandle("engine.dll") + dwClientState);

LocalPlayer* LocalPlayer::Get() {
	return (LocalPlayer*)(*(uintptr_t*)(gameModule + dwLocalPlayer));
}

int LocalPlayer::GetHealth() {
	return *(uintptr_t*)(this + m_iHealth);
}

int LocalPlayer::GetTeam() {
	return *(uintptr_t*)(this + m_iTeamNum);
}

Vector3 LocalPlayer::GetOrigin() {
	float x = *(float*)((uintptr_t)this + m_vecOrigin);
	float y = *(float*)((uintptr_t)this + m_vecOrigin + 4);
	float z = *(float*)((uintptr_t)this + m_vecOrigin + 8) +  *(float*)((uintptr_t)this + m_vecViewOffset + 0x8);

	Vector3 pos = Vector3(x, y, z);

	return pos;
		
}

float LocalPlayer::GetDistance(Player* player) {
	Vector3 local_pos = GetOrigin();
	Vector3 player_pos = player->GetBones();
	return calcDistance(local_pos.x, local_pos.y, local_pos.z, player_pos.x, player_pos.y, player_pos.z);
}

void LocalPlayer::AimAt(Player* target) {
	Vector3 local_pos = GetOrigin();
	Vector3 target_pos = target->GetBones();

	std::pair<float, float>p = calcAngle(local_pos.x, local_pos.y, local_pos.z, target_pos.x, target_pos.y, target_pos.z);

	*(float*)(engineModule + dwClientState_ViewAngles) = std::get<0>(p);
	*(float*)(engineModule + dwClientState_ViewAngles + 0x4) = std::get<1>(p);
}

