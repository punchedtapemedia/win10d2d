#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include "basewindow.h"

class MainWindow : public BaseWindow<MainWindow> {
public:
    MainWindow(LPCWSTR lpWindowName,
               DWORD dwStyle,
               DWORD dwExStyle = 0,
               int x = CW_USEDEFAULT,
               int y = CW_USEDEFAULT,
               int nWidth = CW_USEDEFAULT,
               int nHeight = CW_USEDEFAULT,
               HWND hWndParent = 0,
               HMENU hMenu = 0)
               { BaseWindow::Create(lpWindowName, dwStyle, dwExStyle, x, y, nWidth, nHeight, hWndParent, hMenu); };

    PCWSTR ClassName() const override { return L"Sample Window Class"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};
