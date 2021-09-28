#include <Windows.h>

template<typename T> T RPM(uintptr_t address) {
    try { return *(T*)address; }
    catch (...) { return T(); }
}

template<typename T> void WPM(uintptr_t address, T value) {
    try { *(T*)address = value; }
    catch (...) { return; }

}
