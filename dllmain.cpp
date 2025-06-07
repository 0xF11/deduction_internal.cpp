// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "everything.h"
#include "mem.h"
#include <iostream>

/* NOTES START */
/* Anything in the code starting with h i.e. hRandomstuff = clientside host modifiables
/* Anything in the code starting with cl i.e. clRandomstuff = clientside stuff, like health, shirt color etc
/* This game is kinda weird imo, Alot of different clientside things are in different spots.
/* Anything listed as p, i.e. pHealth = other players health

/* NOTES END */
DWORD WINAPI Hackthread(HMODULE hModule)
{
    uintptr_t modbase = (uintptr_t)GetModuleHandle(L"GameAssembly.dll");
    uintptr_t unitybase = (uintptr_t)GetModuleHandle(L"UnityPlayer.dll");
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "COMMANDS\n";
    std::cout << "\nF9 - IF YOU ARE CHANGING SERVERS - PRESS NUM_0, This will prevent crashes in the menu. - \n";
    std::cout << "F9 - THIS DISABLES EVERYTHING THAT CRASHES THE GAME WHEN IN THE MENU! YOU WILL HAVE TO REENABLE IT -\n\n";
    std::cout << "F1 - sethealth high\n";
    std::cout << "F2 - Set your shirt to an unobtainable color. (If female it will be white)\n";
    std::cout << "F3 - Set your tasks, Kill cooldown, & Meeting Cooldown timer to 0\n";
    std::cout << "F4 - teleport up, perfect height for impostor room\n";
    std::cout << "F5 - Set self to impostor (clientside) - All actions work, can go thru doors etc\n";
    std::cout << "F6 - You will be set as a supervisor (Your vote will be worth 2 votes.)\n";
    std::cout << "LCTRL - Teleport down - Perfect height for tunnels. on construction \n";

    bool b_clHealth = 0, b_clShirt = 0, b_clImpostorStatus = 0, b_clSupervisorStatus = 0;
    bool b_hKill = 0, b_hMeetingCool = 0, b_hTasks = 0;
    bool b_YValU = 0, b_YValD = 0;
    bool bDisable = 0;
    // bool bDisable = 0;


   


    while (true)
    {

        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }
        if (GetAsyncKeyState(VK_F1) & 1)
        {
            b_clHealth = !b_clHealth;
        }
        if (GetAsyncKeyState(VK_F2) & 1)
        {
            b_clShirt = !b_clShirt;
        }
        if (GetAsyncKeyState(VK_F3) & 1)
        {
            b_hKill = !b_hKill;
        }
        if (GetAsyncKeyState(VK_F3) & 1)
        {
            b_hMeetingCool = !b_hMeetingCool;
        }
        if (GetAsyncKeyState(VK_F3) & 1)
        {
            b_hTasks = !b_hTasks;
        }
        if (GetAsyncKeyState(VK_F4) & 1)
        {

            b_YValU = !b_YValU;
            // this will host hat change to impostor
        }
        if (GetAsyncKeyState(VK_LCONTROL) & 1)
        {

            b_YValD = !b_YValD;
            // this will host hat change to impostor
        }

        if (GetAsyncKeyState(VK_F5) & 1)
        {
            !b_clSupervisorStatus;
            b_clImpostorStatus = !b_clImpostorStatus;
        }
        if (GetAsyncKeyState(VK_F6) & 1)
        {
            !b_clImpostorStatus;
            b_clSupervisorStatus = !b_clSupervisorStatus;
        }

        if (GetAsyncKeyState(VK_F9) & 1)
        {
            bDisable = !bDisable;
        }

        if (bDisable)
        {
            !b_YValD, !b_YValU, !b_clHealth, !b_clImpostorStatus, !b_clSupervisorStatus;
        }
        // DISABLE CRASHERS / FIX BROKEN STUFF, SORRY I AM A BEGINNER :P





        // - SERVERSIDE - PLAYER STUFF -//
        if (b_YValU)
        {
            uintptr_t floater = mem::FindDMAAddy(unitybase + 0x01A07E40, { 0x20, 0x68, 0xc0, 0x60, 0x0, 0x1fc });
            float* yval = (float*)floater;
            *yval = 2.916171789f;
        }
        if (b_YValD)
        {
            uintptr_t floater = mem::FindDMAAddy(unitybase + 0x01A07E40, { 0x20, 0x68, 0xc0, 0x60, 0x0, 0x1fc });
            float* yvald = (float*)floater;
            *yvald = 2.286319256f;
        }

        if (b_clShirt)
        {
            *(int*)mem::FindDMAAddy(modbase + 0x02BED6F8, { 0xb8, 0x10, 0x20, 0xD4 }) = 100; // shirt shit
        }

        if (b_clHealth)
        {

            while (true) {

                *(int*)mem::FindDMAAddy(modbase + 0x02BED6F8, { 0xb8, 0x10, 0x20, 0xE0 }) = 25550; // deduction health stuff
                Sleep(5);
            }
        }


        if (b_clImpostorStatus)
        {
            // sets you to impostor, letting you interact w/ doors, see who else is impostor etc 
            // NOTES - CAN ONLY SEE WHO ELSE IS IMPOSTOR IF THIS IS SET PRIOR TO GAME STARTING
            // YOU DO NOT HAVE THE SAME RED COLORED TEXT ABOVE YOUR NAME IF YOU MANUALLY CHANGE THIS.
            //!b_clSupervisorStatus;
            *(int*)mem::FindDMAAddy(modbase + 0x02BED6F8, { 0xb8, 0x10, 0x20, 0xEC }) = 2;
        }

        if (b_clSupervisorStatus)
        {
            // This sets you to supervisor 
            // Supervisor makes your vote worth 2 votes.
            //!b_clImpostorStatus;
            *(int*)mem::FindDMAAddy(modbase + 0x02BED6F8, { 0xb8, 0x10, 0x20, 0xEC }) = 4;
        }





        // - CLIENTSIDE - HOST STUFF - //
        if (b_hKill)// kinda just wrote this for myself and practice purposes, AIO key will be included in code.
        {

            // drf = dereference
            // drfhkill - Dereference our host kill time


            uintptr_t drfhKill = mem::FindDMAAddy(modbase + 0x02C36778, { 0xb8, 0x8, 0x28 });
            // Hey, I want to make an integer that i can modify (int* ourkill)
            // I want whatever integer is stored there to overwrite the value stored in drfhKill.
            int* ourkill = (int*)drfhKill;
            // Our value.
            *ourkill = 0;
        }
        if (b_hMeetingCool)
        {
            *(int*)mem::FindDMAAddy(modbase + 0x02C36778, { 0xb8, 0x8, 0x30 }) = 0;
        }
        if (b_hTasks)
        {
            *(int*)mem::FindDMAAddy(modbase + 0x02C36778, { 0xb8, 0x8, 0x24 }) = 0;
        }





        // Hey, Make killstuff this address in memory.


            //Is our variable we can write to
        // We want to write to killstuff w/ whats inside of killcool

       // *(int*)mem::FindDMAAddy(modbase + 0x02BED6F8, { 0xb8, 0x8, 0x28 }) = 0;
    }



   
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Hackthread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

