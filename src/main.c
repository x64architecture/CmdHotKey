
/*
 * Copyright (C) 2014 Kurt Cancemi
 */
 
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <shellapi.h>
#include <stdio.h>

OSVERSIONINFO osvi;
SHELLEXECUTEINFO shExInfo = { 0 };
MSG msg;

BOOL IsWindows7OrGreater()
{

	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&osvi);

	return ((osvi.dwMajorVersion > 6) ||
		((osvi.dwMajorVersion == 6) && (osvi.dwMinorVersion >= 1)));
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	char profilepath[250];
	ExpandEnvironmentStrings("%USERPROFILE%", profilepath, 250);

	shExInfo.cbSize = sizeof(shExInfo);
	shExInfo.fMask = SEE_MASK_DEFAULT;
	shExInfo.hwnd = 0; // Handle
	shExInfo.lpVerb = "open"; // Action to preform
	shExInfo.lpFile = "cmd.exe"; // Application to open
	shExInfo.lpDirectory = (LPCSTR)profilepath; // Application current directory
	shExInfo.nShow = SW_SHOW; // Show application

	if (IsWindows7OrGreater()) // The MOD_NOREPEAT flag is supported on Windows 7+
	{
		RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 0x54); // 0x54 = T key
		RegisterHotKey(NULL, 2, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 0x51); // 0x51 = Q key
		MessageBox(NULL,
			(LPCSTR)"HotKey 'CTRL+ALT+T (Start CMD), CTRL+ALT+Q (Quit)' registered, using MOD_NOREPEAT flag.\n",
			(LPCSTR)"Notice",
			MB_ICONINFORMATION | MB_OK);
		while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				//printf("WM_HOTKEY received\n");
				switch (msg.wParam) // Switch HotKey id
				{
				case 1: // HotKey 1
					ShellExecuteEx(&shExInfo);
					break;
				case 2: // HotKey 2
					UnregisterHotKey(NULL, 1);
					UnregisterHotKey(NULL, 2);
					exit(0);
					break;
				}
			}
		}
	}
	else
	{
		RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT, 0x54); // 0x54 = T key
		RegisterHotKey(NULL, 2, MOD_CONTROL | MOD_ALT, 0x51); // 0x51 = Q key
		MessageBox(NULL,
			(LPCSTR)"HotKey 'CTRL+ALT+T (Start CMD) & CTRL+ALT+Q (Quit)' registered.\n",
			(LPCSTR)"Notice",
			MB_ICONINFORMATION | MB_OK);
		while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				//printf("WM_HOTKEY received\n");
				switch (msg.wParam) // Switch HotKey id
				{
				case 1: // HotKey 1
					ShellExecuteEx(&shExInfo);
					break;
				case 2: // HotKey 2
					UnregisterHotKey(NULL, 1);
					UnregisterHotKey(NULL, 2);
					exit(0);
					break;
				}
			}
		}
	}
}