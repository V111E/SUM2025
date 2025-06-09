/* FILE NAME  : rndprim.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 09.06.2025
 * PURPOSE    : 3D animation project.
 *          Common declaration module.
 */

#include "rnd.h"

VOID VE7_RndProjSet( VOID )
{
  DBL rx, ry;
 
  rx = ry = VE7_RndProjSize;
  if (VE7_RndFrameW > VE7_RndFrameH)
    rx *= (DBL)VE7_RndFrameW / VE7_RndFrameH;
  else
    ry *= (DBL)VE7_RndFrameH / VE7_RndFrameW;
 
  VE7_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      VE7_RndProjDist, VE7_RndProjFarClip);
  VE7_RndMatrVP = MatrMulMatr(VE7_RndMatrView, VE7_RndMatrProj);
}
 
VOID VE7_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  VE7_RndMatrView = MatrView(Loc, At, Up);
  VE7_RndMatrVP = MatrMulMatr(VE7_RndMatrView, VE7_RndMatrProj);
}

//VE7_RndCamSet(VecSet1(5), VecSet1(0), VecSet(0, 1, 0));

/*
VOID VE7_RndPrimDraw( VE7PRIM *Pr, MATR World )
{
  MATR wvp = MatrMulMatr(World, VE7_RndMatrVP);
    VEC p = VecMulMatr(Prim->V[i], wvp);
 
    pnts[i].x = (INT)((P.X + 1) * VE7_RndFrameW / 2);
    pnts[i].y = (INT)((-P.Y + 1) * VE7_RndFrameH / 2);
}
*/




