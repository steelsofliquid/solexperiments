#include <windows.h>
#include <string>
#include <fstream>

// Global Variables
HINSTANCE hInst;
HWND hWndEdit;

// Function Declarations
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void CreateEditControl(HWND hWnd);
void CreateFileMenu(HWND hWnd);
std::string GetWindowTextString(HWND hWnd);
void HandleSaveCommand(HWND hWnd);

// IDs for menu items
#define IDM_FILE_NEW    1001
#define IDM_FILE_OPEN   1002
#define IDM_FILE_SAVE   1003
#define IDM_FILE_SAVEAS 1004
#define IDM_FILE_EXIT   1005

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Save the instance handle in a global variable
    hInst = hInstance;

    // Register the window class
    const char CLASS_NAME[] = "WordProcessorClass";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hWnd = CreateWindow(
        CLASS_NAME,
        "Word Processor",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hWnd == NULL)
    {
        return 0;
    }

    CreateEditControl(hWnd);
    CreateFileMenu(hWnd);

    // Show the window
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Message loop
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDM_FILE_NEW:
            // TODO: Handle "New" command
            return 0;

        case IDM_FILE_OPEN:
            // TODO: Handle "Open" command
            return 0;

        case IDM_FILE_SAVE:
            HandleSaveCommand(hWnd);
            return 0;

        case IDM_FILE_SAVEAS:
            // TODO: Handle "Save As" command
            return 0;

        case IDM_FILE_EXIT:
            PostQuitMessage(0);
            return 0;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_SIZE:
        if (hWndEdit != NULL)
        {
            // Resize the edit control to fit the window
            RECT rcClient;
            GetClientRect(hWnd, &rcClient);
            MoveWindow(hWndEdit, rcClient.left, rcClient.top, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, TRUE);
        }
        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

void CreateEditControl(HWND hWnd)
{
    // Create an edit control that fills the window
    hWndEdit = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "",
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
        0, 0, 0, 0,
        hWnd,
        NULL,
        hInst,
        NULL
    );

    //

