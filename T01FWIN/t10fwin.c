
/* FILE NAME  : t01fwin.c
 * PROGRAMMER : VG4
 * LAST UPDATE: 02.06.2025
 * PURPOSE    : ??? WinAPI project.
 *              Startup entry-point module.
 */
 
/* Main startup program function.
 * ARGUMENTS:
 *   - application instance handle:
 *       HINSTANCE hInstance;
 *   - previouse application instance handle
 *     (not used, alway NULL):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - command line window show parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) system error level value.
 */
#define _WIN32_WINNT 0x0500
#include <windows.h>

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
  wc.hCursor = LoadCursor(NULL, IDC_NO);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
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
    "WOOOOOOOOOOOOOOOOOOOOW",
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

/* End of 'WinMain' function */
 
/* Window handle function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 *   - message type (see WM_***):
 *       UINT Msg;
 *   - message 'word' parameter:
 *       WPARAM wParam;
 *   - message 'long' parameter:
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  

  switch (Msg)
  {
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    Ellipse(hDC, 500, 300, 800, 500);
    SelectObject(hDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hDC, RGB(0, 100, 0));
    Ellipse(hDC, 600, 340, 700, 440);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;  
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MainWinFunc' function */
 
/* END OF 't01fwin.c' FILE */