/* FILE NAME  : rnd.h
 * PROGRAMMER : VE7
 * LAST UPDATE: 09.06.2025
 * PURPOSE    : 3D animation project.
 *          Common declaration module.
 */
#include "def.h"

extern HWND VE7_hRndWnd;        /* Work window handle */
extern HDC VE7_hRndDCFrame;     /* Work window memory device context  */
extern HBITMAP VE7_hRndBmFrame; /* Work window background bitmap handle */
extern INT VE7_RndFrameW, VE7_RndFrameH; /* Work window size */

extern DBL
  VE7_RndProjSize,     /* Project plane fit square */
  VE7_RndProjDist,     /* Distance to project plane from viewer (near) */
  VE7_RndProjFarClip;  /* Distance to project far clip plane (far) */
 
extern MATR
  VE7_RndMatrView, /* View coordinate system matrix */
  VE7_RndMatrProj, /* Projection coordinate system matrix */
  VE7_RndMatrVP;   /* Stored (View * Proj) matrix */
 
VOID VE7_RndEnd( VOID );

VOID VE7_RndStart( VOID );

VOID VE7_RndCopyFrame( HDC hDC );

VOID VE7_RndInit( HWND hWnd );

VOID VE7_RndClose( VOID );

VOID VE7_RndResize( INT W, INT H );

VOID VE7_RndProjSet( VOID );









 