
#include "exit.h"
#include <Windows.h>
#include <Psapi.h>
#include "scan.h"

bool started = false;

void setupHook(void) {
    if (started) return;
    started = true;
    AllocConsole();
    //freopen("CONOUT$", "w", stdout);
    HMODULE jvmModule = GetModuleHandle(L"jvm.dll");
    if (jvmModule == NULL) {
        puts("jvm.dll module not found!");
        return;
    }
    MODULEINFO moduleinfo;
    HANDLE procHandle = GetCurrentProcess();
    GetModuleInformation(procHandle, jvmModule, &moduleinfo, sizeof(moduleinfo));
    CloseHandle(procHandle);
    //use if necessary
    //uintptr_t found = ps_find_idastyle("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 8B F9 8B 0D 11 4B 63 00 FF 15 E3 B3 45 00 48 8B D8 C7 80 70 02 00 00 05 00 00 00", (uintptr_t)moduleinfo.EntryPoint, moduleinfo.SizeOfImage);
    void* found = GetProcAddress(jvmModule, "JVM_Halt");
    if (found)
    {
        if (MH_Initialize() != MH_OK) {
            puts("Something went wrong while initializing hooks");
            return;
        }

        if (MH_CreateHook((void*)found, (void*)hookedExit, NULL) != MH_OK) {
            puts("Hook failed!");
            return;
        }

        if (MH_EnableHook((void*)found) != MH_OK) {
            puts("Hook failed!");
        }
        puts("Hook has been initialized and enabled!");
    }
}

void hookedExit(int status) {
	//puts("¯\_(ツ)_/¯");
}

