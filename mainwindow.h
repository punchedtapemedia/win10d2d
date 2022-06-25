#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include "basewindow.h"
#include <d2d1.h>
#pragma comment(lib, "d2d1")

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

    PCWSTR ClassName() const override
    { return L"Sample Window Class"; }

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

    long long getFrameCount() { return frame_counter; };

private:
    ID2D1Factory *pFactory{nullptr};
    ID2D1HwndRenderTarget *pRenderTarget{nullptr};
    ID2D1SolidColorBrush *pBrush{nullptr};
    D2D1_ELLIPSE ellipse;
    long long frame_counter{0};

    void CalculateLayout();
    HRESULT CreateGraphicsResources();
    void DiscardGraphicsResources();
    void OnPaint();
    void Resize();
};
