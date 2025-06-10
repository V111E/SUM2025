/* FILE NAME  : rndbase.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 09.06.2025
 * PURPOSE    : 3D animation project.
 *          Common declaration module.
 */

#include "rnd.h"


VOID VE7_RndInit( HWND hWnd )
{
  HDC hDC;
  VE7_hRndWnd = hWnd;
  hDC = GetDC(hWnd);
  VE7_hRndDCFrame = CreateCompatibleDC(hDC);
  VE7_hRndBmFrame = NULL;
  ReleaseDC(hWnd, hDC);

  VE7_RndResize(100, 100);
  VE7_RndCamSet(VecSet(8, 8, 0), VecSet(0, 2, 0), VecSet(0, 1, 0));
}                       

VOID VE7_RndClose( VOID )
{
  DeleteObject(VE7_hRndBmFrame);
  DeleteDC(VE7_hRndDCFrame);
}

VOID VE7_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(VE7_hRndWnd);

  VE7_RndFrameW = W;
  VE7_RndFrameH = H;
  if (VE7_hRndBmFrame)
    DeleteObject(VE7_hRndBmFrame);
  VE7_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(VE7_hRndWnd, hDC);
  SelectObject(VE7_hRndDCFrame, VE7_hRndBmFrame);

  VE7_RndProjSet();
}


VOID VE7_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, VE7_RndFrameW, VE7_RndFrameH,
    VE7_hRndDCFrame, 0, 0, SRCCOPY);
}

VOID VE7_RndStart( VOID )
{
  SelectObject(VE7_hRndDCFrame, GetStockObject(NULL_PEN));
  SelectObject(VE7_hRndDCFrame, GetStockObject(DC_BRUSH));
  SetDCBrushColor(VE7_hRndDCFrame, RGB(0, 0, 0));
  Rectangle(VE7_hRndDCFrame, 0, 0, VE7_RndFrameW + 1, VE7_RndFrameH + 1);

  SetDCBrushColor(VE7_hRndDCFrame, RGB(0, 130, 130));
  SelectObject(VE7_hRndDCFrame, GetStockObject(DC_PEN));
  SetDCPenColor(VE7_hRndDCFrame, RGB(0, 130, 130));

}

VOID VE7_RndEnd( VOID )
{
}

VOID VE7_RndProjSet( VOID )
{
  DBL rx, ry;
 
  rx = ry = VE7_RndProjSize;
  if (VE7_RndFrameW > VE7_RndFrameH)
    rx *= (DBL)VE7_RndFrameW / VE7_RndFrameH;
  else
    ry *= (DBL)VE7_RndFrameH / VE7_RndFrameW;
 
  VE7_RndMatrProj = MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2, VE7_RndProjDist, VE7_RndProjFarClip);
  VE7_RndMatrVP = MatrMulMatr(VE7_RndMatrView, VE7_RndMatrProj);
}

VOID VE7_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  VE7_RndMatrView = MatrView(Loc, At, Up);
  VE7_RndMatrVP = MatrMulMatr(VE7_RndMatrView, VE7_RndMatrProj);
}

