/* FILE NAME  : rnd.h
 * PROGRAMMER : VE7
 * LAST UPDATE: 09.06.2025
 * PURPOSE    : 3D animation project.
 *          Common declaration module.
 */
#ifndef __rnd_h_
#define __rnd_h_

#include "def.h"
#include "string.h"

#define GLEW_STATIC
#include <glew.h>

extern HWND VE7_hRndWnd;        /* Work window handle */
extern HDC VE7_hRndDC;     /* Work window  device context  */
extern HGLRC VE7_hRndGC;     /* Work window  device context  */
extern INT VE7_RndFrameW, VE7_RndFrameH; /* Work window size */

extern DBL
  VE7_RndProjSize,     /* Project plane fit square */
  VE7_RndProjDist,     /* Distance to project plane from viewer (near) */
  VE7_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
  VE7_RndMatrView, /* View coordinate system matrix */
  VE7_RndMatrProj, /* Projection coordinate system matrix */
  VE7_RndMatrVP;   /* Stored (View * Proj) matrix */

typedef struct tagve7VERTEX
{
  VEC P;
} ve7VERTEX;

typedef struct tagve7RPIM
{
  ve7VERTEX *V;
  INT NumOfV;

  INT *I;
  INT NumOfI;

  MATR Trans;
} ve7PRIM;
 
VOID VE7_RndEnd( VOID );

VOID VE7_RndStart( VOID );

VOID VE7_RndCopyFrame( VOID );

VOID VE7_RndInit( HWND hWnd );

VOID VE7_RndClose( VOID );

VOID VE7_RndResize( INT W, INT H );

VOID VE7_RndProjSet( VOID );

VOID VE7_RndProjSet( VOID );

VOID VE7_RndCamSet( VEC Loc, VEC At, VEC Up );

VOID VE7_RndPrimFree( ve7PRIM *Pr );

BOOL VE7_RndPrimCreate( ve7PRIM *Pr, INT NoofV, INT NoofI );

VOID VE7_RndPrimDraw( ve7PRIM *Pr, MATR World );

BOOL VE7_RndPrimLoad( ve7PRIM *Pr, CHAR *FileName );

#endif __rnd_h_






 