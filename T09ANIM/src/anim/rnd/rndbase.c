/* FILE NAME  : rndbase.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 09.06.2025
 * PURPOSE    : 3D animation project.
 *          Common declaration module.
 */

#ifndef __rndbase_c_
#define __rndbase_c_

#pragma comment(lib, "opengl32")

#include "rnd.h"
#include "time.h"

VOID VE7_RndInit( HWND hWnd )
{

  VE7_hRndWnd = hWnd;
  
  VE7_hRndGC = GetDC(hWnd);

  VE7_RndResize(30, 30);
  VE7_RndCamSet(VecSet(18, 18, 18), VecSet(0, 0, 0), VecSet(0, 1, 0));
}

VOID VE7_RndClose( VOID )
{
  ReleaseDC(VE7_hRndWnd, VE7_hRndGC);
}

VOID VE7_RndResize( INT W, INT H )
{

  VE7_RndFrameW = W;
  VE7_RndFrameH = H;
  VE7_RndProjSet();
}

VOID VE7_RndCopyFrame( VOID )
{
  SwapBuffers(VE7_hRndDC);
}

VOID VE7_RndStart( VOID )
{

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

#endif /* __rndbase_c_ */
