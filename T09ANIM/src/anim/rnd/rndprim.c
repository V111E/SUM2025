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
  glDeleteVertexArrays(1, &Pr->VA);
  glDeleteBuffers(1, &Pr->VBuf);
  glDeleteBuffers(1, &Pr->IBuf);
  memset(Pr, 0, sizeof(ve7PRIM));
}

VOID VE7_RndPrimCreate( ve7PRIM *Pr, ve7PRIM_TYPE Type,
                        ve7VERTEX *V, INT NoofV, INT *Ind, INT NoofI )
{
  INT i;
  memset(Pr, 0, sizeof(ve7PRIM));

  
  glGenVertexArrays(1, &Pr->VA);

  if (V != NULL && NoofV != 0)
  {
    glBindVertexArray(Pr->VA);

    glGenBuffers(1, &Pr->VBuf);
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ve7VERTEX) * NoofV, V, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(ve7VERTEX),
                          (VOID *)0); /* позици€ */
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(ve7VERTEX),
                          (VOID *)sizeof(VEC)); /* текстурные координаты */
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(ve7VERTEX),
                          (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* нормаль */
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(ve7VERTEX),
                          (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* цвет */

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
    Pr->MinBB = Pr->MaxBB = V[0].P;
    for (i = 1; i < NoofV; i++)
    {
      Pr->MinBB = VecMinVec(Pr->MinBB, V[i].P);
      Pr->MaxBB = VecMaxVec(Pr->MaxBB, V[i].P);
    }
  }

  if (Ind != NULL && NoofI != 0)
  {
    glGenBuffers(1, &Pr->IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, Ind, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    Pr->NumOfElements = NoofI;
  }
  else
    Pr->NumOfElements = NoofV;


  Pr->Trans = MatrIdentity();

}

BOOL VE7_RndPrimLoad( ve7PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT vn = 0, fn = 0;
  ve7VERTEX *V;
  INT *Ind;  
  CHAR Buf[1000];
  INT size;
 
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
 
  size = sizeof(ve7VERTEX) * vn + sizeof(INT) * fn * 3;
  if ((V = malloc(size)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  Ind = (INT *)(V + vn);
 
  rewind(F);
  vn = 0;
  fn = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;
 
      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      V[vn++].P = VecSet(x, y, z);
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
            Ind[fn++] = c0;
            Ind[fn++] = c1;
            Ind[fn++] = c2;
            c1 = c2;
          }
          n++;
        }
        i++;
      }
    }
  }
  fclose(F);
  VE7_RndPrimTriMeshAutoNormals( V, vn, Ind, fn );
  VE7_RndPrimCreate(Pr, VE7_RND_PRIM_TRIMESH, V, vn, Ind, fn);
  free(V);

  return TRUE;
}

VOID VE7_RndPrimTriMeshAutoNormals( ve7VERTEX *V, INT NumOfV, INT *Ind, INT NumOfI )
{
  INT i;
  VEC L = VecNormalize(VecSet(1, 3, 2));
 
  for (i = 0; i < NumOfV; i++)
    V[i].N = VecSet1(0);
 
  for (i = 0; i < NumOfI; i += 3)
  {
    ve7VERTEX 
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
    V[i].C = Vec4SetVec3(VecMulNum(VecSet(1, 0, 0), nl < 0.1 ? 0.1 : nl), 1);
  }
} 

VOID VE7_RndPrimDraw( ve7PRIM *Pr, MATR World )
{

  MATR wvp = MatrMulMatr3(Pr->Trans, World, VE7_RndMatrVP);
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
  glLoadMatrixf(wvp.A[0]);

  glBindVertexArray(Pr->VA);

  if (Pr->IBuf == 0)
    glDrawArrays(GL_TRIANGLES, 0, Pr->NumOfElements);
  else
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(GL_TRIANGLES, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
 
  //glBegin(GL_TRIANGLES);

  //glEnd();
}



