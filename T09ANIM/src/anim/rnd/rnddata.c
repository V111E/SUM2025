/* FILE NAME  : rnddata.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 09.06.2025
 * PURPOSE    : 3D animation project.
 *          Common declaration module.
 */
#include "rnd.h"

HWND VE7_hRndWnd;       
HDC VE7_hRndDC;    
HGLRC VE7_hRndGLRC;
INT VE7_RndFrameW, VE7_RndFrameH; 


DBL
  VE7_RndProjSize = 0.1,     /* Project plane fit square */
  VE7_RndProjDist = 0.1,     /* Distance to project plane from viewer (near) */
  VE7_RndProjFarClip = 6000;  /* Distance to project far clip plane (far) */
 
MATR
  VE7_RndMatrView, /* View coordinate system matrix */
  VE7_RndMatrProj, /* Projection coordinate system matrix */
  VE7_RndMatrVP;   /* Stored (View * Proj) matrix */

VEC VE7_RndCamLoc, VE7_RndCamAt, VE7_RndCamDir, VE7_RndCamRight, VE7_RndCamUp;
 
INT VE7_RndShdAddonI[5];
FLT VE7_RndShdAddonF[5];

/*End of file*/