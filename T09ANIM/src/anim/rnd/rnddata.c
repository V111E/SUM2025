/* FILE NAME  : rnddata.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 09.06.2025
 * PURPOSE    : 3D animation project.
 *          Common declaration module.
 */
#include "rnd.h"

HWND VE7_hRndWnd;       
HDC VE7_hRndDC;    
HGLRC VE7_hRndGC;     
INT VE7_RndFrameW, VE7_RndFrameH; 


DBL
  VE7_RndProjSize = 0.1,     /* Project plane fit square */
  VE7_RndProjDist = 0.1,     /* Distance to project plane from viewer (near) */
  VE7_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */
 
MATR
  VE7_RndMatrView, /* View coordinate system matrix */
  VE7_RndMatrProj, /* Projection coordinate system matrix */
  VE7_RndMatrVP;   /* Stored (View * Proj) matrix */
 
 

