/* FILE NAME  : rndprim.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 09.06.2025
 * PURPOSE    : 3D animation project.
 *          Common declaration module.
 */

#include "rnd.h"
#include <stdio.h>
#include <string.h>


VOID VE7_RndPrimFree( ve7PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  memset(Pr, 0, sizeof(ve7PRIM));
}

BOOL VE7_RndPrimCreate( ve7PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;
 
  memset(Pr, 0, sizeof(ve7PRIM));
  size = sizeof(ve7VERTEX) * NoofV + sizeof(INT) * NoofI;
 
  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  memset(Pr->V, 0, size);
  
  Pr->I = (INT *)(Pr->V + NoofV);
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();
  memset(Pr->V, 0, size);
  return TRUE;
}

VOID VE7_RndPrimDraw( ve7PRIM *Pr, MATR World )
{
  INT i;
  MATR wvp = MatrMulMatr(Pr->Trans, MatrMulMatr(World, VE7_RndMatrVP));
  
  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    /*
    MoveToEx(VE7_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y, NULL);
    LineTo(VE7_hRndDCFrame, pnts[Pr->I[i + 1]].x, pnts[Pr->I[i + 1]].y);
    LineTo(VE7_hRndDCFrame, pnts[Pr->I[i + 2]].x, pnts[Pr->I[i + 2]].y);
    LineTo(VE7_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y);
    */

  }
}

BOOL VE7_RndPrimLoad( ve7PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT vn = 0, fn = 0;
  CHAR Buf[1000];
 
  memset(Pr, 0, sizeof(ve7PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;
 
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      vn++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT i = 2, n = 0;
 
      while (Buf[i] != 0)
      {
        if (Buf[i - 1] == ' ' && Buf[i] != ' ')
          n++;
        i++;
      }
      fn += n - 2;
    }
  }
 
  if (!VE7_RndPrimCreate(Pr, vn, fn * 3))
  {
    fclose(F);
    return FALSE;
  }
 
  rewind(F);
  vn = 0;
  fn = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;
 
      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      Pr->V[vn++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT i = 2, n = 0, c, c0, c1, c2;
 
      while (Buf[i] != 0)
      {
        if (Buf[i - 1] == ' ' && Buf[i] != ' ')
        {
          sscanf(Buf + i, "%d", &c);
          if (c > 0)
            c--;
          else if (c < 0)
            c = vn + c;
 
          if (n == 0)
            c0 = c;
          else if (n == 1)
            c1 = c;
          else
          {
            c2 = c;
            Pr->I[fn++] = c0;
            Pr->I[fn++] = c1;
            Pr->I[fn++] = c2;
            c1 = c2;
          }
          n++;
        }
        i++;
      }
    }
  }
 
  fclose(F);
  return TRUE;
}


 


//VE7_RndCamSet(VecSet1(5), VecSet1(0), VecSet(0, 1, 0));

/*
VOID VE7_RndPrimDraw( VE7PRIM *Pr, MATR World )
{
  MATR wvp = MatrMulMatr(World, VE7_RndMatrVP);
    VEC p = VecMulMatr(Prim->V[i], wvp);
 
    pnts[i].x = (INT)((P.X + 1) * VE7_RndFrameW / 2);
    pnts[i].y = (INT)((-P.Y + 1) * VE7_RndFrameH / 2);
}
*/




