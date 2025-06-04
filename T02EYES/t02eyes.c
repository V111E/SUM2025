#include <windows.h>
#include <math.h>

#include <time.h>


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
    "WOOW",
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



VOID DrawEye( HDC hDC, INT X, INT Y, INT R, INT R1, INT Mx, INT My )
{
  FLOAT k, len;
  INT xc, yc;

  len = sqrt((Mx - X) * (Mx - X) + (My - Y) * (My - Y));
  k = (R - R1) / len;
  xc = (INT)(X + (Mx - X) * k);
  yc = (INT)(Y + (My - Y) * k);
  
  if (len < (R - R1))
  {
    xc = Mx;
    yc = My;
  }

  SelectObject( hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(215, 215, 215));
  Ellipse(hDC, X - R, Y - R, X + R, Y + R);

  SelectObject( hDC, GetStockObject(DC_BRUSH));
  SetDCBrushColor(hDC, RGB(0, 100, 0));
  Ellipse( hDC, xc - R1 , yc + R1, xc + R1, yc - R1);

}


LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  POINT pt;

  static INT W, H;
  static HDC hMemDC;
  static HBITMAP hBm;

  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 0, 1, NULL);
    return 0;

  case WM_SIZE:
    H = HIWORD(lParam);
    W = LOWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    return 0;

  case WM_LBUTTONDOWN:
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;  
  
  case WM_TIMER:
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    SelectObject( hMemDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hMemDC, RGB(0, 0, 0));
    Rectangle(hMemDC, 0, 0, W, H);
    DrawEye( hMemDC, 200, 300, 90, 47, pt.x, pt.y );
    DrawEye( hMemDC, 400, 300, 90, 47, pt.x, pt.y );
    DrawEye( hMemDC, 600, 300, 90, 47, pt.x, pt.y );
    DrawEye( hMemDC, 800, 300, 90, 47, pt.x, pt.y );
    DrawEye( hMemDC, 1000, 300, 90, 47, pt.x, pt.y );


    DrawEye( hMemDC, 1200 + 250 * sin(3 * (double)clock() / CLOCKS_PER_SEC), 700, 90, 47, pt.x, pt.y );

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;

  case WM_ERASEBKGND:
    return 0;

  case WM_DESTROY:
    DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 0);
    PostQuitMessage(0);
    return 0;  
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} 

