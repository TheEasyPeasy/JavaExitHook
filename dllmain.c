﻿#include "pch.h"
#include "psapi.h"
#include <Windows.h>
#include "scan.h"
#include "exit.h"





BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)setupHook, NULL, 0, NULL);
        break;
    }
    return TRUE;
}

