#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define _WIN32_NT 0x0601
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>

#define LAUNCH_HOTKEY_ID 0xB00
#define QUIT_HOTKEY_ID   0xD1E

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    wchar_t profilepath[MAX_PATH];
    if (!ExpandEnvironmentStringsW(L"%USERPROFILE%", profilepath, MAX_PATH))
        return 0;

    SHELLEXECUTEINFO shExecuteInfo = {
        .cbSize = sizeof(SHELLEXECUTEINFO),
        .fMask = SEE_MASK_DEFAULT,
        .lpVerb = L"open",
        .lpFile = L"cmd.exe",
        .lpDirectory = profilepath,
        .nShow = SW_SHOW,
    };

    if (RegisterHotKey(NULL, LAUNCH_HOTKEY_ID, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 'T') == FALSE)
        return 0;
    if (RegisterHotKey(NULL, QUIT_HOTKEY_ID, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 'Q') == FALSE)
        return 0;

    MessageBoxW(
        NULL,
        L"HotKey 'CTRL+ALT+T (Start CMD), CTRL+ALT+Q (Quit)' registered, using MOD_NOREPEAT flag.\n",
        L"Notice",
        MB_ICONINFORMATION | MB_OK);
    MSG msg;
    BOOL ret;
    while ((ret = GetMessageW(&msg, NULL, WM_HOTKEY, WM_HOTKEY)) != 0) {
        if (ret == -1) {
            ExitProcess(0);
        } else {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        if (msg.message != WM_HOTKEY)
            continue;
        switch (msg.wParam) {
            case LAUNCH_HOTKEY_ID:
                ShellExecuteExW(&shExecuteInfo);
                break;
            case QUIT_HOTKEY_ID:
                UnregisterHotKey(NULL, LAUNCH_HOTKEY_ID);
                UnregisterHotKey(NULL, QUIT_HOTKEY_ID);
                PostQuitMessage(1);
                break;
        }
    }
    return 1;
}
