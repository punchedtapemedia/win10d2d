#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include "mainwindow.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow)
{
    MainWindow win(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW);
    ShowWindow(win.Window(), nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0,0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}