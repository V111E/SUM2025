    /* FILE NAME  : main.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 09.06.2025
 * PURPOSE    : 3D animation project.
 *              Common declaration module.
 */

#include "units/units.h"

#define VE7_WND_CLASS_NAME "WINDOW"

LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT CmdShow )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  SetDbgMemHooks();

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

  /* Add units */
  VE7_AnimAddUnit(VE7_UnitCreateBall());
  VE7_AnimAddUnit(VE7_UnitCreateCTRL());

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
  BOOL SaveActivity;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    minmax = (MINMAXINFO *)lParam;
    minmax->ptMinTrackSize.y = 100;
    minmax->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;

  case WM_CREATE:
    VE7_AnimInit(hWnd);
    SetTimer(hWnd, 1, 10, NULL);
    return 0;

  case WM_SIZE:
    VE7_AnimResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 1, 10);
    return 0;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    VE7_AnimRender();
    VE7_AnimCopyFrame();

    EndPaint(hWnd, &ps);
    return 0;  
  
  case WM_ACTIVATE:
    VE7_Anim.IsActive = LOWORD(wParam) != WA_INACTIVE;
    return 0;

  case WM_ENTERSIZEMOVE:
    SaveActivity = VE7_Anim.IsActive;
    VE7_Anim.IsActive = FALSE;
    return 0;
  
  case WM_TIMER:
    VE7_AnimRender();
    VE7_AnimCopyFrame();
    return 0;

  case WM_ERASEBKGND:
    return 1;

  case WM_DESTROY:
    VE7_AnimClose();
    KillTimer(hWnd, 1);
    PostQuitMessage(0);
    return 0;  
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}