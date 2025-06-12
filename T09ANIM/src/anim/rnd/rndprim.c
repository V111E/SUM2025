/* FILE NAME  : rndprim.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 09.06.2025
 * PURPOSE    : 3D animation project.
 *          Common declaration module.
 */

#include "rnd.h"
#include <stdio.h>
#include <string.h>

typedef struct tagve7VERTEX1
{
  VEC P;   /* позици€ */
  VEC2 T;  /* текстурна€ координата */
  VEC N;   /* нормаль */
  VEC4 C;  /* ÷вет (r,g,b,a) */
} ve7VERTEX1;


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
  size = sizeof(ve7VERTEX1) * NoofV + sizeof(INT) * NoofI;
 
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

VOID VE7_RndPrimTriMeshAutoNormals( ve7VERTEX1 *V, INT NumOfV, INT *Ind, INT NumOfI )
{
  INT i;
  VEC L = VecNormalize(VecSet(1, 3, 2));
 
  for (i = 0; i < NumOfV; i++)
    V[i].N = VecSet1(0);
 
  for (i = 0; i < NumOfI; i += 3)
  {
    ve7VERTEX1 
      *P0 = &V[Ind[i]],
      *P1 = &V[Ind[i + 1]],
      *P2 = &V[Ind[i + 2]];
    VEC N = VecNormalize(VecCrossVec(VecSubVec(P1->P, P0->P), VecSubVec(P2->P, P0->P)));
 
    P0->N = VecAddVec(P0->N, N);
    P1->N = VecAddVec(P1->N, N);
    P2->N = VecAddVec(P2->N, N);
  }
 
  for (i = 0; i < NumOfV; i++)
    V[i].N = VecNormalize(V[i].N);
 
  for (i = 0; i < NumOfV; i++)
  {
    FLT nl = VecDotVec(L, V[i].N);
    V[i].C = Vec4SetVec3(VecMulNum(VecSet(0.8, 0.47, 0.30), nl < 0.1 ? 0.1 : nl), 1);
  }
} 

VOID VE7_RndPrimDraw( ve7PRIM *Pr, MATR World )
{
  INT i;
  MATR wvp = MatrMulMatr3(Pr->Trans, World, VE7_RndMatrVP);
  VEC L = VecNormalize(VecSet(1, 3, 2));
 
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
  glLoadMatrixf(wvp.A[0]);
 
  glBegin(GL_TRIANGLES);
  for (i = 0; i < Pr->NumOfI; i++)
  {
    FLT nl = VecDotVec(L, Pr->V[Pr->I[i]].P);
    VEC Color = VecMulNum(VecSet(0.8, 0.47, 0.30), nl < 0.1 ? 0.1 : nl);
 
    glColor3fv(&Color.X);
    glVertex3fv(&Pr->V[Pr->I[i]].P.X);
  }
  glEnd();
}



