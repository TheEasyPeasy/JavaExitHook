#pragma once

#include "MinHook.h"

typedef int(__fastcall* EXITCALL) (int status);


void setupHook(void);

void hookedExit(int status);
