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
  VE7_hWndDCFrame = CreateCompatibleDC(hDC);
  VE7_hRndBmFrame = NULL;

  VE7_RndCamSet(VecSet1(8), VecSet1(4), VecSet(0, 1, 0))
  Release(hWnd, hDC);
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
  //SelectObject pen
  //SelectObject brush null
  //set color pen
  //rectangle dcframe 0, 0, rndframe
}


 
VOID VE7_RndEnd( VOID )
{

}




