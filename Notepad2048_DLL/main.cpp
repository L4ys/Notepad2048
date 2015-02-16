#include <stdio.h>
#include <math.h>
#include <Windows.h>
#define WM_USER_INIT WM_USER+1

enum {
    S0,
    S2,
    S4,
    S8,
    S16,
    S32,
    S64,
    S128,
    S256,
    S512,
    S1024,
    S2048
};

static wchar_t* g_Shape[] = {
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0",
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¢±¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0",
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¢³¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0",
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¢·¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0",
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¢°¢µ¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0",
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¢²¢±¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0",
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¢µ¢³¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0",
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¢°¢±¢·¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0",
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¢±¢´¢µ¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0",
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¢´¢°¢±¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0",
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¢°¢¯¢±¢³¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0",
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¢±¢¯¢³¢·¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0"
    L"¡@¡@¡@¡@¡@¡@\0",
};

static wchar_t* g_welcome = L"\n"
L"        _   __      __                       __   ___   ____  __ __  ____ \n"
L"       / | / /___  / /____  ____  ____ _____/ /  |__ \\ / __ \\/ // / ( __ )\n"
L"      /  |/ / __ \\/ __/ _ \\/ __ \\/ __ `/ __  /   __/ // / / / // /_/ __  |\n"
L"     / /|  / /_/ / /_/  __/ /_/ / /_/ / /_/ /   / __// /_/ /__  __/ /_/ / \n"
L"    /_/ |_/\\____/\\__/\\___/ .___/\\__,_/\\__,_/   /____/\\____/  /_/  \\____/  \n"
L"                        /_/                                               \n"
L"\n"
L"                  NotePad 2048 By Lays, Press N To Start New Game";

static wchar_t* g_gameover = L"\n\n\n\n\n\n\n\n\n\n\n"
 L"       ______                     ____                 \n"
 L"      / ____/___ _____ ___  ___  / __ \\_   _____  _____\n"
 L"     / / __/ __ `/ __ `__ \\/ _ \\/ / / / | / / _ \\/ ___/\n"
 L"    / /_/ / /_/ / / / / / /  __/ /_/ /| |/ /  __/ /    \n"
 L"    \\____/\\__,_/_/ /_/ /_/\\___/\\____/ |___/\\___/_/     \n"
 L"\n\n\n\n\n"
 L"                 Presse N To Start New Game\n\n\n\n\n\n\n";
 
static wchar_t* g_win = L"\n\n\n\n\n\n\n\n\n\n\n"
 L"        __  __               _       ___          __\n"
 L"        \\ \\/ /___  __  __   | |     / (_)___     / /\n"
 L"         \\  / __ \\/ / / /   | | /| / / / __ \\   / / \n"
 L"         / / /_/ / /_/ /    | |/ |/ / / / / /  /_/  \n"
 L"        /_/\\____/\\__,_/     |__/|__/_/_/ /_/  (_)   \n"
L"\n\n\n\n\n"
L"                 Presse N To Start New Game\n\n\n\n\n\n\n";

static HWND g_hNotepad = NULL;
static HWND g_hEdit = NULL;
static WNDPROC g_wpPrevWndProc = NULL;

static bool g_IsGameRunning = false;
static bool g_IsPrinting = false;

static int g_Score;
static int Martix[4][4];
static wchar_t g_GameMsg[256];

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    DWORD lpdwProcessId;
    GetWindowThreadProcessId(hwnd, &lpdwProcessId);
    if ( lpdwProcessId == lParam ) {
        g_hNotepad = hwnd;
        return FALSE;
    }
    return TRUE;
}

void SetGameMsg(wchar_t* msg)
{
    wcscpy(g_GameMsg, msg);
}

int FindEmptyBlock(int list[16][2])
{
    int count = 0;

    for ( int i = 0; i < 4; ++i) {
        for ( int j = 0; j < 4; ++j) {
            if ( !Martix[i][j] ) {
                list[count][0] = i;
                list[count++][1] = j;
            }
        }
    }
    return count;
}

void AddNewBlock(int count)
{
    for ( int i = 0; i < count; ++i ) {
        int list[16][2] = { { 0 }, { 0 } };
        int randomBox = FindEmptyBlock(list);
        if ( !randomBox )
            return;
        else
            randomBox = rand() % randomBox;
        Martix[list[randomBox][0]][list[randomBox][1]] = rand() % 10 >= 9 ? S4: S2;
    }
}

void RefreshScreen()
{
    // Refresh matrix
    wchar_t buffer[1024] = L"";
    wcscat(buffer, L"¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C\r\n");

    for ( int i = 0; i < 4; ++i ) {
        for ( int j = 0; j < 6; ++j ) {
            wcscat(buffer, L"¡U");
            for ( int k = 0; k < 4; ++k ) {
                wcscat(buffer, &g_Shape[Martix[i][k]][j*7]);
                wcscat(buffer, L"¡U");
            }
            wcscat(buffer, L"\r\n");
        }
        wcscat(buffer, L"¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C\r\n");
    }
   
    // Refresh score and message
    wchar_t score[128] = L"";
    wsprintfW(score, L"[+] Score: %5d\r\n", g_Score);
    wcscat(buffer, score);
    wcscat(buffer, g_GameMsg);
    wcscat(buffer, L"\r\n");

    SetWindowText(g_hEdit, buffer);
}

void Print(wchar_t* c, int delay = 0)
{
    for ( size_t i = 0; i < wcslen(c); ++i ) {
        PostMessage(g_hEdit, WM_CHAR, c[i], 1);
        if ( delay )
            Sleep(delay);
    }
}

void PrintMatrix()
{
    Print(L"¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C\n");
    
    for ( int i = 0; i < 4; ++i ) {
        for ( int j = 0; j < 6; ++j ) {
            Print(L"¡U");
            for ( int k = 0; k < 4; ++k ) {
                Print(&g_Shape[Martix[i][k]][j*7]);
                Print(L"¡U");
            }
            Print(L"\n");
        }
        Print(L"¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡C\n");
    }
}

void PrintThread(void* p)
{
    wchar_t* msg = (wchar_t*)p;
    g_IsPrinting = true;

    PostMessage(g_hEdit, WM_SETFOCUS, NULL, NULL);
    PostMessage(g_hEdit, EM_SETSEL, -2, -1);
    
    Print(msg, 5);
    g_IsPrinting = false;
}

void TPrint(wchar_t* msg)
{
    // Print message with a new thread
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PrintThread, msg, NULL, NULL);
}

bool IsGameOver()
{
    for ( int i = 0; i < 4; ++i )
        for ( int j = 0; j < 4; ++j )
            if ( Martix[i][j] == S0 ) // Empty block found
                return false;

    for ( int i = 0; i < 3; ++i)
        for ( int j = 0; j < 3; ++j )
            if ( Martix[i][j] == Martix[i][j+1] ) // Movable
                return false;
            else if ( Martix[i][j] == Martix[i+1][j] ) // Movable
                return false;

    if ( Martix[3][0] == Martix[3][1] || 
         Martix[3][1] == Martix[3][2] ||
         Martix[3][2] == Martix[3][3] ||
         Martix[0][3] == Martix[1][3] ||
         Martix[1][3] == Martix[2][3] ||
         Martix[2][3] == Martix[3][3] ) // Movable
         return false;

    return true;
}

bool IsWin()
{
    for ( int i = 0; i < 4; ++i )
        for ( int j = 0; j < 4; ++j )
            if ( Martix[i][j] == S2048 )
                return true;
    return false;
}

LRESULT APIENTRY MyWndFunc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    switch (uMsg)
    {
    case WM_USER_INIT:
        TPrint(g_welcome);
        break;
    case WM_CHAR:
        if ( lParam != 1 ) // Only accept WM_CHAR from our PostMessage()
            return TRUE;
        break;
    case WM_KEYDOWN: 
        // Copy some shitty game logic code from somewhere LOL
        if ( g_IsGameRunning && !g_IsPrinting ) {
            if ( wParam == VK_UP ) {
                for(int i=0; i<4; ++i){
                    for(int j=0, flag=1; j<3;){
                        if (!Martix[j][i] && flag){	
                            flag = 0;
                            for (int k = j;k<3;k++){
                                if(Martix[k+1][i])
                                    flag = 1;
                                Martix[k][i] = Martix[k+1][i];
                            }
                            Martix[3][i] = S0;
                        } else {
                            flag = 1;
                            j++;
                        }
                    }
                    for (int j=0;j<3;j++){
                        if(Martix[j][i]!= S0 && Martix[j][i] == Martix[j+1][i]){
                            Martix[j][i]++;
                            Martix[j+1][i] = S0;
                            g_Score += (int)pow(2.0, Martix[j][i]);
                            for(int k=j+1; k<3; k++){
                                Martix[k][i] = Martix[k+1][i];
                            }
                            Martix[3][i] = S0;
                        }
                    }
                }
            }
            else if ( wParam == VK_DOWN ) {
                //SetGameMsg(L"You Pressed DOWN!\r\n");
                for(int i=0; i<4; i++){
                    for(int j=3, flag=1; j>0;){
                        if(!Martix[j][i] && flag){	
                            flag = 0;
                            for(int k=j; k>0; k--){
                                if(Martix[k-1][i])
                                    flag = 1;
                                Martix[k][i] = Martix[k-1][i];
                            }
                            Martix[0][i] = 0;
                        }else{
                            flag = 1;
                            j--;
                        }
                    }
                    for(int j=3; j>0; j--){
                        if ( Martix[j][i] != S0 && Martix[j][i]==Martix[j-1][i]){
                            Martix[j][i]++;
                            Martix[j-1][i] = S0;
                            g_Score += (int)pow(2.0, Martix[j][i]);
                            for(int k=j-1; k>0; k--){
                                Martix[k][i] = Martix[k-1][i];
                            }
                            Martix[0][i] = S0;
                        }
                    }
                }
            }
            else if ( wParam == VK_LEFT ) {
                //SetGameMsg(L"You Pressed LEFT!\r\n");
                for(int i=0; i<4; i++){
                    for(int j=0, flag=1; j<3;){
                        if(!Martix[i][j] && flag){	
                            flag = 0;
                            for(int k=j; k<3; k++){
                                if(Martix[i][k+1])
                                    flag = 1;
                                Martix[i][k] = Martix[i][k+1];
                            }
                            Martix[i][3] = S0;
                        }else{
                            flag = 1;
                            j++;
                        }
                    }
                    for(int j=0; j<3; j++){
                        if ( Martix[i][j] != S0 && Martix[i][j] == Martix[i][j+1] ) {
                            Martix[i][j]++;
                            Martix[i][j+1] = S0;
                            g_Score += (int)pow(2.0, Martix[i][j]);

                            for(int k=j+1; k<3; k++){
                                Martix[i][k] = Martix[i][k+1];
                            }
                            Martix[i][3] = S0;
                        }
                    }
                }
            }
            else if ( wParam == VK_RIGHT ) {
               // SetGameMsg(L"You Pressed RIGHT!\r\n");
                for(int i=0; i<4; i++){
                    for(int j=3, flag=1; j>0;){
                        if(!Martix[i][j] && flag){	
                            flag = 0;
                            for(int k=j; k>0; k--){
                                if(Martix[i][k-1])
                                    flag = 1;
                                Martix[i][k] = Martix[i][k-1];
                            }
                            Martix[i][0] = S0;
                        }else{
                            flag = 1;
                            j--;
                        }
                    }
                    for(int j=3; j>0; j--){
                        if ( Martix[i][j] != S0 && Martix[i][j] == Martix[i][j-1]){
                            Martix[i][j]++;
                            Martix[i][j-1] = S0;
                            
                            g_Score += (int)pow(2.0, Martix[i][j]);
                            
                            for(int k=j-1; k>0; k--){
                                Martix[i][k] = Martix[i][k-1];
                            }
                            Martix[i][0] = S0;
                        }
                    }
                }
            
            }
            /* For Debug 
            else if ( wParam == 'R' ) {
                //SetGameMsg(L"You Pressed R!\r\n");
                g_IsGameRunning = false;
                TPrint(g_gameover);
                return TRUE;
            }
            else if ( wParam == 'W' ) {
                //SetGameMsg(L"You Pressed R!\r\n");
                g_IsGameRunning = false;
                TPrint(g_win);
                return TRUE;
            }
            */
            else
                break;

            AddNewBlock(1);

            RefreshScreen();
            SetGameMsg(L"");

            if ( IsWin() ) {
                g_IsGameRunning = false;
                TPrint(g_win);
                return TRUE;
            }
            else if ( IsGameOver() ) {
                g_IsGameRunning = false;
                TPrint(g_gameover);
                return TRUE;
            }
        }
        else if ( wParam == 'N' ) {
            if ( !g_IsGameRunning && !g_IsPrinting) {
                SetGameMsg(L"New Game Started!");
                memset(Martix, S0, 16*4);
                g_Score = 0;
                g_IsGameRunning = true;
                AddNewBlock(2);
                RefreshScreen();
            }
        }                 
        return TRUE;
    }

    return CallWindowProc( g_wpPrevWndProc, hwnd, uMsg, wParam, lParam );
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if ( fdwReason == DLL_PROCESS_ATTACH ) {
        while ( g_hEdit == NULL ) {
            g_hNotepad = FindWindow(L"Notepad", NULL);       
            g_hEdit = GetDlgItem(g_hNotepad, 0xF);
            Sleep(50);
        }

        // Hook winproc
        g_wpPrevWndProc = (WNDPROC)SetWindowLong(g_hEdit, GWLP_WNDPROC, (LONG)MyWndFunc);

        // Start the game!
        if ( g_hEdit != NULL)
            PostMessage(g_hEdit, WM_USER_INIT, NULL, NULL);

        // Init blocks 
        memset(Martix, S0, 16*4);
    }
    
    return TRUE;
}


