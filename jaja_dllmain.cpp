#include "pch.h"
#include <Windows.h>
#include <iostream>



namespace cube {
    constexpr uintptr_t printf = 0x46B060;
    using printf_t = void(*) (const char* format, ...);
}

uintptr_t acBase = (uintptr_t)GetModuleHandle(L"game_executable.exe");


struct Entity {
    char pad[0x4];
    float x;
    float y;
    float z;
    char pad2[0x30];
    float yaw;
    float pitch;
    float roll;
    char pad3[0xAC];
    int health;
    int armor;
    char pad4[0x14];
    int pistol;
    int carbine;
    int shotgun;
    int machinegun;
    int sniper;
    int assaultrife;
};

DWORD WINAPI Ecuador(HMODULE hModule)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    const auto printf = reinterpret_cast<cube::printf_t>(cube::printf);
    DWORD* localPlayer = (DWORD*)(acBase + 0x10F4F4);
    Entity* player = (Entity*)*localPlayer;

    for (;;)
    {
        if (GetAsyncKeyState(0x56))
        {
            printf("Health added");
            player->health++;
            player->x += 5;
        }
        if (GetAsyncKeyState(0x59))
        {
            player->x += 10;
        }
        if (GetAsyncKeyState(0x58))
        {
            player->x -= 10;
        }
        if (GetAsyncKeyState(0x54))
        {
            player->yaw += 20;
            player->pitch += 20;
            player->roll += 20;
        }
        Sleep(5);
    }

}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Ecuador, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
