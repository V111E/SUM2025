    /* FILE NAME  : main.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 09.06.2025
 * PURPOSE    : 3D animation project.
 *              Common declaration module.
 */

#include <time.h>

#include "anim\rnd\rnd.h"

#define VE7_WND_CLASS_NAME "WINDOW"

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
  wc.lpszClassName = VE7_WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error reg win class", "AHTUNG", MB_OK);
    return 0;
  }

  hWnd = 
    CreateWindow(VE7_WND_CLASS_NAME,
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

  while (TRUE)
    if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 1, 0);
  return msg.wParam;
}


LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  MINMAXINFO *minmax;
  static ve7PRIM Pr, PrO;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    minmax = (MINMAXINFO *)lParam;
    minmax->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;

  case WM_CREATE:
    VE7_RndInit(hWnd);
    if (VE7_RndPrimCreate(&Pr, 4, 6))
    {
      Pr.V[0].P = VecSet(0, 0, 0);
      Pr.V[1].P = VecSet(2, 0, 0);
      Pr.V[2].P = VecSet(0, 2, 0);
      Pr.V[3].P = VecSet(2, 2, 0);
 
      Pr.I[0] = 0;
      Pr.I[1] = 1;
      Pr.I[2] = 2;
 
      Pr.I[3] = 2;
      Pr.I[4] = 1;
      Pr.I[5] = 3;
    }
    
    VE7_RndPrimLoad(&PrO, "cow.obj");
    SetTimer(hWnd, 1, 10, NULL);
    return 0;

  case WM_SIZE:
    VE7_RndResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 1, 10);

    return 0;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    VE7_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;  
  
  case WM_TIMER:
    VE7_RndStart();
    VE7_RndPrimDraw(&Pr, MatrRotateY(30 * clock() / 1000.0));
    VE7_RndPrimDraw(&PrO, MatrMulMatr(MatrScale(VecSet(1, 1, 1)), MatrRotateY(30 * clock() /1000)));
    VE7_RndEnd();
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_DESTROY:
    VE7_RndClose();
    VE7_RndPrimFree(&Pr);
    VE7_RndPrimFree(&PrO); 
    KillTimer(hWnd, 1);
    PostQuitMessage(0);
    return 0;  
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}