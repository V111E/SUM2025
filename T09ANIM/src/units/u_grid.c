/* FILE NAME: u_grid.c
 * PURPOSE: units module.
 * PROGRAMMER: VE7
 * DATE: 16.06.2025
 */

#include <stdio.h>

#include "units/units.h"

typedef struct
{
  VE7_UNIT_BASE_FIELDS;
  ve7PRIM Land;
  VEC Pos;
} ve7UNIT_GRID;

static VOID VE7_UnitInit( ve7UNIT_GRID *Uni, ve7ANIM *Ani )
{
  INT w, h, y, x;
  HBITMAP hBm;
  BITMAP bm;
  ve7GRID G;

  if ((hBm = LoadImage(NULL, "bin/heights/map.bmp", IMAGE_BITMAP, 0, 0,
                       LR_LOADFROMFILE | LR_CREATEDIBSECTION)) != NULL)
  {
    GetObject(hBm, sizeof(bm), &bm);
    w = bm.bmWidth;
    h = bm.bmHeight;
    if (bm.bmBitsPixel == 8 && VE7_RndGridCreate(&G, w, h))
    {
      BYTE *Bits = bm.bmBits;
 
      VE7_RndGridCreate(&G, w, h);
      for (y = 0; y < h; y++)
        for (x = 0; x < w; x++)
        {
          INT hgt = Bits[(h - 1 - y) * bm.bmWidthBytes + x];
 
          G.V[y * w + x].P = VecSet(x / (w - 1.0),
                                    hgt / 255.0,
                                    1 - y / (h - 1.0));
        }
      VE7_RndGridAutoNormals(&G);
      VE7_RndPrimFromGrid(&Uni->Land, &G);
      VE7_RndGridFree(&G);
    }
    DeleteObject(hBm);
  }
} 

static VOID VE7_UnitClose( ve7UNIT_GRID *Uni, ve7ANIM *Ani )
{
  VE7_RndPrimFree(&Uni->Land);
} 

static VOID VE7_UnitResponse( ve7UNIT_GRID *Uni, ve7ANIM *Ani )
{
} 

static VOID VE7_UnitRender( ve7UNIT_GRID *Uni, ve7ANIM *Ani )
{
  VE7_RndPrimDraw(&Uni->Land, MatrIdentity());
} 

ve7UNIT * VE7_UnitCreateGrid( VOID )
{ 
  ve7UNIT *Uni;

  if((Uni = VE7_AnimUnitCreate(sizeof(ve7UNIT_GRID))) == NULL)
    return NULL;

  Uni->Init = (VOID *)VE7_UnitInit;
  Uni->Close = (VOID *)VE7_UnitClose;
  Uni->Response = (VOID *)VE7_UnitResponse;
  Uni->Render = (VOID *)VE7_UnitRender;
  return Uni;
} 
