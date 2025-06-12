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

extern HWND VE7_hRndWnd;      
extern HDC VE7_hRndDC;
extern HGLRC VE7_hRndGLRC;
extern INT VE7_RndFrameW, VE7_RndFrameH;

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
  VEC2 T; 
  VEC N;  
  VEC4 C; 
} ve7VERTEX;

typedef enum tagve7PRIM_TYPE
{
  VE7_RND_PRIM_POINTS,   /* Array of points  – GL_POINTS */
  VE7_RND_PRIM_LINES,    /* Line segments (by 2 points) – GL_LINES */
  VE7_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles – GL_TRIANGLES */
} ve7PRIM_TYPE;

typedef struct tagve7RPIM
{
  ve7PRIM_TYPE Type; /* Primitive type */
  INT
    VA,              /* Vertex array Id */
    VBuf,            /* Vertex buffer Id */
    IBuf;            /* Index buffer Id (if 0 - use only vertex buffer) */
  INT NumOfElements; /* Number of indices/vecrtices */
  VEC MinBB, MaxBB;  /* Bound box */
  MATR Trans;   /* Additional transformation matrix */
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

VOID VE7_RndPrimCreate( ve7PRIM *Pr, ve7PRIM_TYPE Type,
                        ve7VERTEX *V, INT NoofV, INT *Ind, INT NoofI );

VOID VE7_RndPrimDraw( ve7PRIM *Pr, MATR World );

BOOL VE7_RndPrimLoad( ve7PRIM *Pr, CHAR *FileName );

VOID VE7_RndPrimTriMeshAutoNormals( ve7VERTEX *V, INT NumOfV, INT *Ind, INT NumOfI );

VOID VE7_RndPrimDraw( ve7PRIM *Pr, MATR World );

VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                             INT Length, const CHAR *Message,
                             const VOID *UserParam );

#endif __rnd_h_






 