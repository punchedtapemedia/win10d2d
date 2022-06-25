#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include "mainwindow.h"
#include <chrono>
#include <string>

class Time {
public:
    Time ()
    {
        start_ = std::chrono::high_resolution_clock::now();
    }

    long long time()
    {
        std::chrono::duration<long long, std::nano> elap_ = std::chrono::high_resolution_clock::now() - start_;
        return elap_.count();
    }
private:
    std::chrono::high_resolution_clock::time_point start_;
};


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow)
{
    MainWindow win(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW);
    ShowWindow(win.Window(), nCmdShow);

    MSG msg;
    bool is_running = true;
    Time t;
    long long prev_time = 0;
    long long delta_t_ns = 0;

    long long time_cur = t.time();

    while (is_running)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                is_running = false;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        long long frame_count = win.getFrameCount();
        if (frame_count % 60 == 0)
        {
            time_cur = t.time();
            delta_t_ns = time_cur - prev_time;
            prev_time = time_cur;

            long long fps = (long) (60 / ((double)delta_t_ns / 1.0e9));
//            long long fps = (long long) (frame_count / ((double)time_cur / 1.0e9));

//            std::string win_title = "WINDOW: " + std::to_string(fps) + " fps";
            std::string win_title = "WINDOW: " + std::to_string(frame_count) + " frames " + std::to_string(time_cur) + " ns " + std::to_string(fps) + " fps";
            std::wstring stmp = std::wstring(win_title.begin(), win_title.end());
            SetWindowTextW(win.Window(), stmp.c_str());
        }

        InvalidateRect(win.Window(), NULL, false);
        UpdateWindow(win.Window());
    }




    return 0;
}