/* FILE NAME: globe.c
 * PROGRAMMER: VE7
 * DATE: 06.06.2025
 * PURPOSE: globus
 */
#include <math.h>
#include <windows.h>
#include "globe.h"
#include "mth.h"
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
      GLB_Geom[i][j].X = R * sin(theta) * sin(phi);
      GLB_Geom[i][j].Y = R * cos(theta);
      GLB_Geom[i][j].Z = R * sin(theta) * cos(phi);
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
 
  NewP.X = P.X * co - P.Y * si;
  NewP.Y = P.X * si + P.Y * co;
  NewP.Z = P.Z;
  return NewP;
}

VEC RotateX( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
 
  NewP.Y = P.Y * co - P.Z * si;
  NewP.Z = P.Y * si + P.Z * co;
  NewP.X = P.X;
  return NewP;
}
VEC RotateY( VEC P, DBL Angle )
{
  VEC NewP;
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
 
  NewP.Z = P.Z * co - P.X * si;
  NewP.X = P.Z * si + P.X * co;
  NewP.Y = P.Y;
  return NewP;
}
VOID GLB_Draw( HDC hDC )
{
  INT i, j, s = 1;
  VEC P;
  DBL t = (double)clock() / CLOCKS_PER_SEC;
  static POINT pnts[GRID_H][GRID_W];


  /* Build projections */
  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      P = RotateZ(RotateX(RotateY(GLB_Geom[i][j], cos(t) * 10), tan(t / 2) * 10), 1 / tan(t) * 5);

      pnts[i][j].x = (INT)(P.X + GLB_Ws / 2);
      pnts[i][j].y = (INT)(-P.Y + GLB_Hs / 2);
    }

  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      Ellipse(hDC, pnts[i][j].x - s, pnts[i][j].y - s,
        pnts[i][j].x + s, pnts[i][j].y + s);
    }

  SetDCPenColor(hDC, RGB(0, 150, 110));
  for (i = 0; i < GRID_H; i++)
  {
    MoveToEx(hDC, pnts[i][0].x, pnts[i][0].y, NULL);
    for (j = 0; j < GRID_W; j++)
      LineTo(hDC, pnts[i][j].x , pnts[i][j].y);
  }

}

