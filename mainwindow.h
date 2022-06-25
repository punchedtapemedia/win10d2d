#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include "basewindow.h"

class MainWindow : public BaseWindow<MainWindow> {
public:
    PCWSTR ClassName() const override { return L"Sample Window Class"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};
