#ifndef FILE_FOO_SEEN
#define FILE_FOO_SEEN

#include <Windows.h>
#include "offsets.h"

uintptr_t gameModule = (uintptr_t)(GetModuleHandle("client.dll"));
uintptr_t engineModule = *(uintptr_t*)((uintptr_t)GetModuleHandle("engine.dll") + dwClientState);

#endif
