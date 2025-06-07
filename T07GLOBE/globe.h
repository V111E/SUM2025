/* FILE NAME: t07globe.c
 * PROGRAMMER: VE7
 * DATE: 06.06.2025
 * PURPOSE: globus
 */

#include <windows.h>

typedef double DBL;


#define GRID_W 53
#define GRID_H 31


typedef struct 
{
  DBL X, Y, Z;
} VEC;

VOID GLB_Init( DBL R );
VOID GLB_Resize( INT Ws, INT Hs );
VOID GLB_Draw( HDC hDC );
