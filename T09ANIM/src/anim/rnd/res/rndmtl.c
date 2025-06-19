/* FILE NAME  : rndmtl.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 14.06.2025
 * PURPOSE    : 3D animation project.
 */

#include "anim\anim.h"
 
ve7MATERIAL VE7_RndMtlGetDef( VOID )
{
  ve7MATERIAL def_mtl =
  {
    "Default",
    {0.1, 0.1, 0.1},
    {0.90, 0.90, 0.90},
    {0.30, 0.30, 0.30},
    30, 1,
    {-1, -1, -1, -1, -1, -1, -1, -1},
    0
  };
 
  return def_mtl;
}
 
VOID VE7_RndMtlInit( VOID )
{
  ve7MATERIAL def = VE7_RndMtlGetDef();
 
  VE7_RndMaterialsSize = 0;
  VE7_RndMtlAdd(&def);
}

VOID VE7_RndMtlClose( VOID )
{
  ve7MATERIAL def = {
    "Default",
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    0, 1,
    {0, 0, 0, 0, 0, 0, 0, 0},
    0
  };
  VE7_RndMtlAdd(&def);
  VE7_RndMaterialsSize = 0;

}
 
INT VE7_RndMtlAdd( ve7MATERIAL *Mtl )
{
  if (VE7_RndMaterialsSize >= VE7_MAX_MATERIALS)
    return 0;
  VE7_RndMaterials[VE7_RndMaterialsSize] = *Mtl;
  return VE7_RndMaterialsSize++;
}
 
UINT VE7_RndMtlApply( INT MtlNo )
{
  UINT prg;
  INT prg_no;
  ve7MATERIAL *mtl;
  INT loc, i;
 
  /* Set material pointer */
  if (MtlNo < 0 || MtlNo >= VE7_RndMaterialsSize)
    MtlNo = 0;
  mtl = &VE7_RndMaterials[MtlNo];
 
  /* Set shader program Id */
  prg_no = mtl->ShdNo;
  if (prg_no < 0 || prg_no >= VE7_RndShadersSize)
    prg_no = 0;
  prg = VE7_RndShaders[prg_no].ProgId;
 
  if (prg == 0)
    return 0;
 
  glUseProgram(prg);
 
  if ((loc = glGetUniformLocation(prg, "Time")) != -1)
    glUniform1f(loc, VE7_Anim.Time);
  if ((loc = glGetUniformLocation(prg, "GlobalTime")) != -1)
    glUniform1f(loc, VE7_Anim.GlobalTime);
 
  /* Set shading parameters */
  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);

  /* Set textures */
  for (i = 0; i < 8; i++)
  {
    CHAR tname[] = "IsTexture0";
 
    tname[9] = '0' + i;
    if (mtl->Tex[i] != -1)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, VE7_RndTextures[mtl->Tex[i]].TexId);
    }
    if ((loc = glGetUniformLocation(prg, tname)) != -1)
      glUniform1i(loc, mtl->Tex[i] != -1);
  }
  return prg;
}
 
ve7MATERIAL * VE7_RndMtlGet( INT MtlNo )
{
  if (MtlNo < 0 || MtlNo >= VE7_RndMaterialsSize)
    MtlNo = 0;
  return &VE7_RndMaterials[MtlNo];

}

/*End of file*/