/* FILE NAME: globe.c
 * PROGRAMMER: VE7
 * DATE: 06.06.2025
 * PURPOSE: globus
 */
#include <math.h>
#include <windows.h>
#include "globe.h"
#include <time.h>

DOUBLE pi = 3.14159265359;

static INT GLB_Ws, GLB_Hs;
static VEC GLB_Geom[GRID_H][GRID_W];

VOID GLB_Init( DBL R )
{
  INT i, j;

  for (i = 0; i < GRID_H; i++)
  {
    for (j = 0; j < GRID_W; j++)
    {
      DBL theta = i * pi / (GRID_H - 1);
      DBL phi = j * 2 * pi / (GRID_W - 1);
      GLB_Geom[i][j].x = R * sin(theta) * sin(phi);
      GLB_Geom[i][j].y = R * cos(theta);
      GLB_Geom[i][j].z = R * sin(theta) * cos(phi);
    }
  }
}

VOID GLB_Resize( INT Ws, INT Hs)
{
  GLB_Ws = Ws;
  GLB_Hs = Hs;
}

/*  for (i = 0; i < GRID_H; i++)
  {
    MoveToEx(hDC, pnts[i][0].x, pnts[i][0].y, NULL);
    for (j = 1; j < GRID_W; j++)
      LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
  }
*/
VEC RotateZ( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
 
  NewP.x = P.x * co - P.y * si;
  NewP.y = P.x * si + P.y * co;
  NewP.z = P.z;
  return NewP;
}

VEC RotateX( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
 
  NewP.y = P.y * co - P.z * si;
  NewP.z = P.y * si + P.z * co;
  NewP.x = P.x;
  return NewP;
}
VEC RotateY( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
 
  NewP.z = P.z * co - P.x * si;
  NewP.x = P.z * si + P.x * co;
  NewP.y = P.y;
  return NewP;
}
VOID GLB_Draw( HDC hDC )
{
  INT i, j, s = 2;
  VEC P;
  DBL t = (double)clock() / CLOCKS_PER_SEC;
  static POINT pnts[GRID_H][GRID_W];
  
  /* Build projections */
  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      P = RotateZ(RotateX(RotateY(GLB_Geom[i][j], cos(t) * 10), tan(t) * 10), t );
      pnts[i][j].x = (INT)(P.x + GLB_Ws / 2);
      pnts[i][j].y = (INT)(-P.y + GLB_Hs / 2);
    }
  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      Ellipse(hDC, pnts[i][j].x - s, pnts[i][j].y - s,
        pnts[i][j].x + s, pnts[i][j].y + s);
    }

  SetDCPenColor(hDC, RGB(0, 110, 110));
  for (i = 0; i < GRID_H; i++)
  {
    MoveToEx(hDC, pnts[i][0].x, pnts[i][0].y, NULL);
    for (j = 0; j < GRID_W; j++)
      LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
  }
}



