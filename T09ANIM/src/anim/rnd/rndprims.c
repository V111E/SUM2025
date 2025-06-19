/* FILE NAME  : rndprims.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 17.06.2025
 * PURPOSE    : 3D animation project.
 *              Rendering primitives handle module.
 */
 
#include <stdio.h>
#include <string.h>

#include "rnd.h"
 
BOOL VE7_RndPrimsCreate( ve7PRIMS *Prs, INT NumOfPrims )
{
  memset(Prs, 0, sizeof(ve7PRIMS));
  if ((Prs->Prims = malloc(sizeof(ve7PRIM) * NumOfPrims)) == NULL)
    return FALSE;
  Prs->NumOfPrims = NumOfPrims;
  Prs->Trans = MatrIdentity();
  return TRUE;
} 

VOID VE7_RndPrimsFree( ve7PRIMS *Prs )
{
  free(Prs->Prims);
  memset(Prs, 0, sizeof(ve7PRIMS));
}

VOID VE7_RndPrimsDraw( ve7PRIMS *Prs, MATR World )
{
  INT i;
  MATR m = MatrMulMatr(Prs->Trans, World);

  VE7_RndShdAddonI[1] = Prs->NumOfPrims;
 
  /* Draw all nontransparent primitives */ 
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (VE7_RndMtlGet(Prs->Prims[i].MtlNo)->Trans == 1)
      VE7_RndShdAddonI[0] = i, VE7_RndPrimDraw(&Prs->Prims[i], m);
 
  /* Draw all transparent primitives */ 
  glEnable(GL_CULL_FACE);
 
  /* Draw all front-face-culling */ 
  glCullFace(GL_FRONT);

  for (i = 0; i < Prs->NumOfPrims; i++)
    if (VE7_RndMtlGet(Prs->Prims[i].MtlNo)->Trans != 1)
      VE7_RndShdAddonI[0] = i, VE7_RndPrimDraw(&Prs->Prims[i], m);
 
  /* Draw all back-face-culling */ 
  glCullFace(GL_BACK);
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (VE7_RndMtlGet(Prs->Prims[i].MtlNo)->Trans != 1)
      VE7_RndShdAddonI[0] = i, VE7_RndPrimDraw(&Prs->Prims[i], m);

 
  glDisable(GL_CULL_FACE);
} 

BOOL VE7_RndPrimsLoad( ve7PRIMS *Prs, CHAR *FileName )
{
  FILE *F;
  INT flen, p, m, t;
  BYTE *mem, *ptr;
  DWORD Sign; /* == "G3DM" */
  DWORD NumOfPrims;
  DWORD NumOfMaterials;
  DWORD NumOfTextures;
 
  memset(Prs, 0, sizeof(ve7PRIMS));
  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;
 
  /* Obtain file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
 
  /* Allocate memory for whole file */
  if ((mem = malloc(flen)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  rewind(F);
  fread(mem, 1, flen, F);
  fclose(F);
 
  ptr = mem;
  /* Signature */
  Sign = *(DWORD *)ptr;
  ptr += 4;
  if (Sign != *(DWORD *)"G3DM")
  {
    free(mem);
    return FALSE;
  }
 
  /* Quantities */
  NumOfPrims = *(DWORD *)ptr;
  ptr += 4;
  NumOfMaterials = *(DWORD *)ptr;
  ptr += 4;
  NumOfTextures = *(DWORD *)ptr;
  ptr += 4;
 
  if (!VE7_RndPrimsCreate(Prs, NumOfPrims))
  {
    free(mem);
    return FALSE;
  }

  /* Primitives */
  for (p = 0 ; p < (INT)NumOfPrims; p++)
  {
    DWORD NumOfVertexes;
    DWORD NumOfFacetIndexes;  /* num of facets * 3 */
    DWORD MtlNo;              /* Material number in table below (in material section) */
    ve7VERTEX *V;
    INT *Ind;
 
    NumOfVertexes = *(DWORD *)ptr;
    ptr += 4;
    NumOfFacetIndexes = *(DWORD *)ptr;
    ptr += 4;
    MtlNo = *(DWORD *)ptr;
    ptr += 4;
    V = (ve7VERTEX *)ptr;
    ptr += sizeof(ve7VERTEX) * NumOfVertexes;
    Ind = (INT *)ptr;
    ptr += sizeof(INT) * NumOfFacetIndexes;
 
    VE7_RndPrimCreate(&Prs->Prims[p], VE7_RND_PRIM_TRIMESH, V, NumOfVertexes, Ind, NumOfFacetIndexes);
    Prs->Prims[p].MtlNo = VE7_RndMaterialsSize + MtlNo;
  }
 
  /* Materials */
  for (m = 0 ; m < (INT)NumOfMaterials; m++)
  {
    struct
    {
       CHAR Name[300]; /* Material name */
       VEC Ka, Kd, Ks;     /* Ambient, diffuse, specular coefficients */
       FLT Ph;             /* Phong power coefficient – shininess */
       FLT Trans;          /* Transparency factor */
       DWORD Tex[8];       /* Texture references 
                            * (8 time: texture number in G3DM file, -1 if no texture) */
       /* Shader information */
       CHAR ShaderString[300]; /* Additional shader information */
       DWORD Shader;       /* Shader number (uses after load into memory) */
    } *fmat;
    ve7MATERIAL mtl = VE7_RndMtlGetDef();
 
    fmat = (VOID *)ptr;
    ptr += sizeof(*fmat);
    strncpy(mtl.Name, fmat->Name, VE7_STR_MAX - 1);
    mtl.Ka = fmat->Ka;
    mtl.Kd = fmat->Kd;
    mtl.Ks = fmat->Ks;
    mtl.Ph = fmat->Ph;
    mtl.Trans = fmat->Trans;
    for (t = 0; t < 8; t++)
      mtl.Tex[t] = fmat->Tex[t] == -1 ? -1 : VE7_RndTexturesSize + fmat->Tex[t];
    VE7_RndMtlAdd(&mtl);
  }
 
  /* Textures */
  for (t = 0 ; t < (INT)NumOfTextures; t++)
  {
    CHAR *Name;
    DWORD W, H, C;
 
    Name = (CHAR *)ptr;
    ptr += 300;
    W = *(DWORD *)ptr;
    ptr += 4;
    H = *(DWORD *)ptr;
    ptr += 4;
    C = *(DWORD *)ptr;
    ptr += 4;
    VE7_RndTexAddImg(Name, W, H, C, ptr);
    ptr += C * W * H;
  }
 
  free(mem);
  return TRUE;
} /* End of 'VE7_RndPrimsDraw' function */
 
/* END OF 'rndprims.c' FILE */