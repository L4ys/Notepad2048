#include <stdio.h>
#include <Windows.h>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) 

int main( int argc, char *argv[] )
{
    wchar_t* wszDll = L"Notepad2048.dll";
    wchar_t wszPath[MAX_PATH] = L"";

    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};

    GetSystemDirectory(wszPath, MAX_PATH);
    wcscat(wszPath, L"\\notepad.exe");

    CreateProcess(wszPath, NULL, NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);

    LPVOID Param = VirtualAllocEx(pi.hProcess, NULL, MAX_PATH, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

    WriteProcessMemory(pi.hProcess, Param, (LPVOID)wszDll, wcslen(wszDll) * 2 + 1, NULL);

    HANDLE hThread = CreateRemoteThread(pi.hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryW, Param, CREATE_SUSPENDED, NULL);  

    ResumeThread(pi.hThread);
    while ( FindWindow(L"Notepad", NULL) == NULL )
        Sleep(50);

    ResumeThread(hThread);
    CloseHandle(hThread);

    return 0;
}
