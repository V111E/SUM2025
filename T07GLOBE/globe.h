/* FILE NAME: t07globe.c
 * PROGRAMMER: VE7
 * DATE: 06.06.2025
 * PURPOSE: globus
 */

#include <windows.h>

typedef double DBL;


#define GRID_W 100
#define GRID_H 90


VOID GLB_Init( DBL R );
VOID GLB_Resize( INT Ws, INT Hs );
VOID GLB_Draw( HDC hDC );
