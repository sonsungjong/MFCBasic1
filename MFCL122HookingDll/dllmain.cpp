// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

HINSTANCE g_hInstance;
HHOOK gh_next_hook;
HWND gh_target_wnd;

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
        break;
    }
    g_hInstance = hModule;

    return TRUE;
}

LRESULT CALLBACK KeyboardProc(int a_code, WPARAM wParam, LPARAM lParam)
{
    if (a_code == HC_ACTION) {
        if (gh_target_wnd != NULL) {
            ::PostMessage(gh_target_wnd, 27001, wParam, lParam);
        }
    }
    return CallNextHookEx(gh_next_hook, a_code, wParam, lParam);
}

extern "C" __declspec(dllexport) void InstallKeyHook(HWND ah_target_wnd)
{
    gh_target_wnd = ah_target_wnd;
    gh_next_hook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, g_hInstance, 0);

}

extern "C" __declspec(dllexport) void UnInstallKeyHook()
{
    UnhookWindowsHookEx(gh_next_hook);
}