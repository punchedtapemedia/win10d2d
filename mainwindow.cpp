#include "mainwindow.h"
#include "utils.h"

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
            if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
            {
                return -1;
            }
            return 0;

        case WM_DESTROY:
            DiscardGraphicsResources();
            SafeRelease(&pFactory);
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
            OnPaint();
            return 0;

        case WM_SIZE:
            Resize();
            return 0;
    }

    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void MainWindow::CalculateLayout()
{
    if (pRenderTarget == NULL)
        return;

    D2D1_SIZE_F size = pRenderTarget->GetSize();
    const float x = size.width / 2.0;
    const float y = size.height / 2.0;
    const float radius = min(x, y);
    ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
}

HRESULT MainWindow::CreateGraphicsResources()
{
    HRESULT hr = S_OK;
    if (pRenderTarget != NULL)
        return hr;

    RECT rc;
    GetClientRect(m_hwnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

    hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &pRenderTarget);

    if (SUCCEEDED(hr))
    {
        const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);
        hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);

        if (SUCCEEDED(hr))
        {
            CalculateLayout();
        }
    }
    return hr;
}

void MainWindow::DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush);
}

void MainWindow::OnPaint()
{
    HRESULT hr = CreateGraphicsResources();
    if (!SUCCEEDED(hr))
        return;

    frame_counter++;

    PAINTSTRUCT ps;
    BeginPaint(m_hwnd, &ps);

    pRenderTarget->BeginDraw();
    pRenderTarget->Clear( D2D1::ColorF(D2D1::ColorF::SkyBlue) );
    pRenderTarget->FillEllipse(ellipse, pBrush);

    hr = pRenderTarget->EndDraw();
    if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
    {
        DiscardGraphicsResources();
    }
    EndPaint(m_hwnd, &ps);
}

void MainWindow::Resize()
{
    if (pRenderTarget == NULL)
        return;

    RECT rc;
    GetClientRect(m_hwnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

    pRenderTarget->Resize(size);
    CalculateLayout();
    InvalidateRect(m_hwnd, NULL, FALSE);
}