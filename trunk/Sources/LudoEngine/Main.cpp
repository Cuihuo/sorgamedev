///////////////////////////////
// Filename: LudoEngine.cpp
// Description: Defines the entry point for the application.
///////////////////////////////

#include "LudoCore/LudoGlobal.h"
#include "Main.h"
#include "LudoEngine.h"
#include "LudoRenderer/LudoRenderer.h"
#include "LudoCore/LudoMemory.h"
#include "LudoCore/ErrorLogger.h"
#include "LudoCore/LudoStringManager.h"
#include "LudoCore/LudoTimer.h"
#include "LudoCore/LudoInput.h"
#include "LudoCore/InputKeyboard.h"
#include "LudoCore/InputMouse.h"
#include <Windows.h>
#include <WinUser.h>

#define MAX_LOADSTRING 100
static const int NO_RETURN = -999;

// Global Variables:
HINSTANCE hInst;                                // current instance
TCHAR szTitle[MAX_LOADSTRING];                    // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                ChangeDirToAppDir();

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    ChangeDirToAppDir();
    HANDLE hDetectPreviousVersion = CreateMutex(NULL, TRUE, L"DetectLudoPreviousVersionMutex");
    if(GetLastError() == ERROR_ALREADY_EXISTS)
    {
        // Application is already running
        return 0;
    }

    LudoMemory::GetInstance( false );
    ErrorLogger::GetInstance( false );

     // TODO: Place code here.
    MSG msg;
    HACCEL hAccelTable;

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_LUDOENGINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LUDOENGINE));

    // Main message loop:
    int returnValue = NO_RETURN;
    while (returnValue == NO_RETURN)
    {
        if (!LudoEngine::GetInstance()->UpdateGame())
        {
            returnValue = 0;            
        }

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {                
                returnValue = (int) msg.wParam;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    LudoEngine::GetInstance()->Destroy();
    LudoStringManager::GetInstance()->Destroy();
    LudoTimer::GetInstance()->Destroy();
    LudoMemory::GetInstance()->Destroy();

    CloseHandle(hDetectPreviousVersion);
    return returnValue;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style            = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra        = 0;
    wcex.cbWndExtra        = 0;
    wcex.hInstance        = hInstance;
    wcex.hIcon            = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LUDOENGINE));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName    = MAKEINTRESOURCE(IDC_LUDOENGINE);
    wcex.lpszClassName    = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   DWORD window_format = WS_EX_APPWINDOW;

   LANGID language = GetUserDefaultUILanguage();
   // RTL_LANG: list of rtl languages
   // need to get the bottom 10 bits (thats the location of the primary language mask)
   if ( (language & 0x3FF) == LANG_ARABIC || (language & 0x3FF) == LANG_HEBREW)
   {
       window_format = WS_EX_LAYOUTRTL;
   }

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowEx(window_format, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 800, 600, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   ErrorLogger::GetInstance()->Init(L"ErrorLog.txt", hWnd);
   LudoEngine::GetInstance()->GetRender()->Init(hWnd,800,600);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;

    switch (message)
    {
    case WM_KEYDOWN:
        LudoEngine::GetInstance()->GetInput()->GetKeyboard()->SetKeyPressed((int)wParam);
        break;
    case WM_KEYUP:
        LudoEngine::GetInstance()->GetInput()->GetKeyboard()->SetKeyUnpressed((int)wParam);
        break;
    case WM_MOUSEMOVE:
    case WM_NCMOUSEMOVE:
        LudoEngine::GetInstance()->GetInput()->GetMouse()->SetMouseMouse(LOWORD(lParam),HIWORD(lParam));
        break;
    case WM_MOUSEWHEEL:
        break;
    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


void ChangeDirToAppDir()
{
    wchar_t buf[MAX_PATH+1];
    GetModuleFileName(NULL, buf, MAX_PATH);
    int exeNameLength = (int)(wcslen(buf));
    for(int i = exeNameLength - 1; i > 0; i--)
    {
        if(buf[i]=='\\')
        {
            buf[i] = '\0';
            break;
        }
    }

    SetCurrentDirectory(buf);
}
