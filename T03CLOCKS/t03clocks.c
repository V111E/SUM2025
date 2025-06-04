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

VOID DrawEye( HDC hDC, INT X, INT Y, INT R, INT R1, INT Mx, INT My )
{
  double k, len;
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
  SetDCBrushColor(hDC, RGB(0, 0, 0));
  Ellipse( hDC, xc - R1 , yc + R1, xc + R1, yc - R1);

}

VOID DrawHand( HDC hDC, INT xc, INT yc , INT len, DOUBLE time, COLORREF Color, POINT *Pnt )
{
  DOUBLE pi = 3.14159265359, a;
  HPEN hPen, hOldPen;
  //SetDCPenColor(hDC,)

  hPen = CreatePen(PS_SOLID, 7, Color);
  hOldPen = SelectObject(hDC, hPen);
  a = (time + time / 60) * pi / 30;
  MoveToEx(hDC, xc + len * sin(a), yc - len * cos(a), NULL);
  if (Pnt != NULL)
    Pnt->x = xc + len * sin(a), Pnt->y = yc - len * cos(a);
  LineTo(hDC, xc, yc);
  SelectObject(hDC, GetStockObject(DC_PEN));
  DeleteObject(hPen);
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  POINT pt, pt1, pt2;
  SYSTEMTIME st;
  static INT W, H, size, t, t1, i;
  static HDC hMemDC, hMemDCClk, hMemDCAnd, hMemDCXor;
  static BITMAP bm;
  static HBITMAP hBm, hBmClk, hBmAnd, hBmXor;

  switch (Msg)
  {
  case WM_CREATE:
 
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    hMemDCClk = CreateCompatibleDC(hDC);

    hMemDCAnd = CreateCompatibleDC(hDC);
    hMemDCXor = CreateCompatibleDC(hDC);

    ReleaseDC(hWnd, hDC);
    hBmClk = LoadImage(NULL, "chas.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hBmAnd = LoadImage(NULL, "and.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hBmXor = LoadImage(NULL, "xor.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    SelectObject(hMemDCClk, hBmClk);
    SelectObject(hMemDCXor, hBmXor);
    SelectObject(hMemDCAnd, hBmAnd);
    SetTimer(hWnd, 0, 0.01, NULL);
    return 0;

  case WM_SIZE:
    H = HIWORD(lParam); 
    W = LOWORD(lParam);
    size = W < H ? W : H;
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);

    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    return 0;

  case WM_PAINT:

    GetLocalTime(&st);
    hDC = BeginPaint(hWnd, &ps);
    GetObject(hBmClk, sizeof(BITMAP), &bm);
    SelectObject(hMemDC, GetStockObject(NULL_PEN));
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCPenColor(hMemDC, RGB(255, 0, 0));
    SetDCBrushColor(hMemDC, RGB(100, 100, 100));
    Rectangle(hMemDC, 0, 0, W + 1, H + 1);
    SetStretchBltMode(hMemDC, COLORONCOLOR);
    StretchBlt(hMemDC, (W - size) / 2, (H - size) / 2, size, size, hMemDCClk, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
    
    DrawHand(hMemDC, W / 2, H / 2, size * 0.495, st.wSecond * 60, RGB(0, 255, 0), &pt);
    DrawHand(hMemDC, W / 2, H / 2, size * 0.446, st.wMinute * 60 , RGB(0, 0, 255), &pt1);
    DrawHand(hMemDC, W / 2, H / 2, size * 0.336, (st.wHour % 12) * 5, RGB(255, 0, 0), NULL);
    GetCursorPos(&pt2);
    ScreenToClient(hWnd, &pt2);

    SetDCBrushColor(hMemDC, RGB(255, 0, 0));
    DrawEye(hMemDC, W / 2 * 1.6, H / 2 * 1.1, size * 0.05, size * 0.02, pt.x, pt.y);
    DrawEye(hMemDC, W / 2 * 0.4, H / 2 * 0.9, size * 0.05, size * 0.02, pt1.x, pt1.y);
    DrawEye(hMemDC, W / 2 * 0.4, H / 2 * 1.1, size * 0.05, size * 0.02, pt2.x, pt2.y);

    GetObject(hBmAnd, sizeof(BITMAP), &bm);

    t = (double)clock() / CLOCKS_PER_SEC * 5;

    for (i = 0; i < 20; i++)
    {
      t1 = t - 2 * i;
      BitBlt(hMemDC, W / 2 + 200 * sin(2 * t1), W / 2 - 500 + 200 * cos(3 * t1), bm.bmWidth, bm.bmHeight, hMemDCAnd, 0, 0, SRCAND);
      BitBlt(hMemDC, W / 2 + 200 * sin(2 * t1), W / 2 - 500 + 200 * cos(3 * t1), bm.bmWidth, bm.bmHeight, hMemDCXor, 0, 0, SRCINVERT);

    }
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;  
  
  case WM_TIMER:
    Rectangle(hMemDC, 0, 0, W, H);
     /* + 250 * sin(1 * (double)clock() / CLOCKS_PER_SEC)*/
    InvalidateRect(hWnd, NULL, TRUE);
    return 0;

  case WM_ERASEBKGND:
    return 0;

  case WM_DESTROY:
    DeleteDC(hMemDCAnd);
    DeleteDC(hMemDCXor);
    DeleteObject(hBmAnd);
    DeleteObject(hBmXor);

    DeleteDC(hMemDCClk);
    DeleteObject(hBmClk);
    DeleteDC(hMemDC);
    DeleteObject(hBm);
    KillTimer(hWnd, 0);
    PostQuitMessage(0);
    return 0;  
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} 

