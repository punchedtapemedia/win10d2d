#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdexcept>

template <class DERIVED_TYPE>
class BaseWindow {
public:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        DERIVED_TYPE *pThis = nullptr;

        if (uMsg == WM_NCCREATE)
        {
            CREATESTRUCT *pCreate = (CREATESTRUCT*)lParam;
            pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

            pThis->m_hwnd = hwnd;
        }
        else
        {
            pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        }

        if (pThis)
        {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }
        else
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    BaseWindow() = default;


    HWND Window() const { return m_hwnd; };

protected:
    BOOL Create(LPCWSTR lpWindowName,
                DWORD dwStyle,
                DWORD dwExStyle = 0,
                int x = CW_USEDEFAULT,
                int y = CW_USEDEFAULT,
                int nWidth = CW_USEDEFAULT,
                int nHeight = CW_USEDEFAULT,
                HWND hWndParent = 0,
                HMENU hMenu = 0)
    {
        WNDCLASS wc = {0};

        wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = ClassName();

        auto showerror = [](){
            LPVOID lpMsgBuf;
            FormatMessage(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    GetLastError(),
                    0, // Default language
                    (LPTSTR) &lpMsgBuf,
                    0,
                    NULL
            );
            // Process any inserts in lpMsgBuf.
            // ...
            // Display the string.
            MessageBox( NULL, (LPCTSTR)lpMsgBuf, L"Error", MB_OK | MB_ICONINFORMATION );
            // Free the buffer.
            LocalFree( lpMsgBuf );
        };

        auto result = RegisterClass(&wc);
        if (result == NULL)
        {
            showerror();
            throw std::runtime_error("Failed to register class");
        }

        m_hwnd = CreateWindowEx(
                dwExStyle, ClassName(), lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this);

        if (m_hwnd == NULL)
        {
            showerror();
            throw std::runtime_error("Failed to register class");
        }
    }

    virtual PCWSTR ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

    HWND m_hwnd{NULL};
};
