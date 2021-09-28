#include "includes.h"

static uintptr_t gameModule;
static uintptr_t engineModule;

Player* GetClosestPlayer() {
	LocalPlayer* localPlayer = LocalPlayer::Get();
	Player* closest_player = NULL;
	float old_dist = 1000000;

	for (int i = 0; i < 32; i++) {
		Player* player = Player::Get(i);

		if (!player || !(*(uintptr_t*)player || (uintptr_t)player == (uintptr_t)localPlayer)) {
			continue;
		}
		if (player->GetTeam() == localPlayer->GetTeam() || player->GetHealth() < 1) {
			continue;
		}

		float dist = localPlayer->GetDistance(player);

		if (dist < old_dist) {
			closest_player = player;
			old_dist = dist;
		}

	}
	return closest_player;
}

void Aimbot() {
	LocalPlayer* localPlayer = LocalPlayer::Get();
	if (localPlayer) {
		Player* target = GetClosestPlayer();
		if (GetAsyncKeyState(VK_MENU) && target) {
			localPlayer->AimAt(target);
		}
	}
}

void Radar() {
	for (int i = 0; i < 32; i++) {
		Player* player = Player::Get(i);
		if (player) {
			*(bool*)(player + m_bSpotted) = true;
		}
	}
}

void NoFlash() {
	LocalPlayer* localPlayer = LocalPlayer::Get();
	if (localPlayer) {
		*(float*)(localPlayer + m_flFlashMaxAlpha) = 0.0;
	}
}

DWORD WINAPI MainThread(HMODULE hModule) {

	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	gameModule = (uintptr_t)(GetModuleHandle("client.dll"));
	engineModule = *(uintptr_t*)((uintptr_t)GetModuleHandle("engine.dll") + dwClientState);

	std::cout << "Hello there!";

	while (true) {

		Aimbot();
		Radar();
		NoFlash();

		if (GetAsyncKeyState(VK_END)) {
			break;
		}
	}

	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved){
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


