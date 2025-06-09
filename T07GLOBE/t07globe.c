/* FILE NAME: t07globe.c
 * PROGRAMMER: VE7
 * DATE: 06.06.2025
 * PURPOSE: globus
 */

#include <windows.h>
#include <math.h>
#include <time.h>

#include "globe.h"
#include "mth.h"


#define WND_CLASS_NAME "WINDOW"


LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT CmdShow )
{


  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_GRAYTEXT;
  wc.hCursor = LoadCursor(NULL, IDC_CROSS);
  wc.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error reg win class", "AHTUNG", MB_OK);
    return 0;
  }

  hWnd = 
    CreateWindow(WND_CLASS_NAME,
    "WOW",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT,
    NULL,
    NULL,
    hInstance,
    NULL);

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}


LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  static INT W, H, size, t, t1, i;
  static HDC hMemDC;
  static BITMAP bm;
  static HBITMAP hBm;
  DBL tim = clock() / (DBL)CLOCKS_PER_SEC;
  double SyncTime;
  DBL GLB_Time, GLB_DeltaTime, GLB_FPS;
  BOOL GLB_IsPause;
  LONG StartTime, OldTime, PauseTime, OldFPSTime, FrameCount;

  switch (Msg)
  {
  case WM_CREATE:
 
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    GLB_Init(200);
    ReleaseDC(hWnd, hDC);
    Rectangle(hMemDC, 0, 0, W + 1, H + 1);

    StartTime = OldTime = OldFPSTime = clock();
    FrameCount = 0;
    GLB_IsPause = FALSE;
    SetTimer(hWnd, 1, 10, NULL);

    return 0;

  case WM_KEYDOWN:
    if (wParam == VK_F2)
    {
      KillTimer(hWnd, 1);
    }

  case WM_SIZE:
    H = HIWORD(lParam); 
    W = LOWORD(lParam);

    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);

    GLB_Resize(W, H);

    SelectObject(hMemDC, hBm);
    return 0;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    Rectangle(hMemDC, 0, 0, W + 1, H + 1);

    SelectObject(hMemDC, GetStockObject(DC_PEN));
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCPenColor(hMemDC, RGB(0, 0, 0));
    SetDCBrushColor(hMemDC, RGB(255, 255, 255));

    GLB_Draw(hMemDC);

    SetDCBrushColor(hMemDC, RGB(0, 0, 0));
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;  
  
  case WM_TIMER:



    InvalidateRect(hWnd, NULL, TRUE);
    return 0;

  case WM_ERASEBKGND:
    return 0;

  case WM_DESTROY:
   
    DeleteDC(hMemDC);
    DeleteObject(hBm);
    KillTimer(hWnd, 0);
    PostQuitMessage(0);
    return 0;  
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}