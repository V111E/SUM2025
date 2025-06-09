/* FILE NAME  : rnddata.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 09.06.2025
 * PURPOSE    : 3D animation project.
 *          Common declaration module.
 */
#include "rnd.h"

HWND VE7_hRndWnd;        /* Work window handle */
HDC VE7_hRndDCFrame;     /* Work window memory device context  */
HBITMAP VE7_hRndBmFrame; /* Work window background bitmap handle */
INT VE7_RndFrameW, VE7_RndFrameH; /* Work window size */

DBL
  VE7_RndProjSize = 0.1,     /* Project plane fit square */
  VE7_RndProjDist = 0.1,     /* Distance to project plane from viewer (near) */
  VE7_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */
 
MATR
  VE7_RndMatrView, /* View coordinate system matrix */
  VE7_RndMatrProj, /* Projection coordinate system matrix */
  VE7_RndMatrVP;   /* Stored (View * Proj) matrix */
 
 

