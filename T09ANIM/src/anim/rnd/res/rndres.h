/* FILE NAME  : rndres.h
 * PROGRAMMER : VE7
 * LAST UPDATE: 13.06.2025
 * PURPOSE    : 3D animation project.
 */
#ifndef __rndres_h_
#define __rndres_h_

#include "def.h"

VOID VE7_RndResInit( VOID );

VOID VE7_RndResClose( VOID );

#define VE7_STR_MAX 300

typedef struct tagve7SHADER
{
  CHAR Name[VE7_STR_MAX];
  INT ProgId;
} ve7SHADER;

typedef struct tagve7MATERIAL
{
  CHAR Name[VE7_STR_MAX]; /* Material name */
 
  /* Illumination coefficients */    
  VEC Ka, Kd, Ks;           /* Ambient, diffuse, specular coefficients */
  FLT Ph;                   /* Phong power coefficient */
 
  FLT Trans;                /* Transparency factor */
 
  INT Tex[8];               /* Texture references from texture table (or -1) */
 
  INT ShdNo;                /* Shader number in shader table */
} ve7MATERIAL;

#define VE7_MAX_MATERIALS 300
ve7MATERIAL VE7_RndMaterials[VE7_MAX_MATERIALS]; /* Array of materials */
INT VE7_RndMaterialsSize;                        /* Materials array */ 

#define VE7_MAX_SHADERS 30
extern ve7SHADER VE7_RndShaders[VE7_MAX_SHADERS];
extern INT VE7_RndShadersSize;

VOID VE7_RndShdInit( VOID );

VOID VE7_RndShdClose( VOID );

INT VE7_RndShdAdd( CHAR *ShaderFileNamePrefix );

VOID VE7_RndShdUpdate( VOID );

VOID VE7_RndMtlInit( VOID );

VOID VE7_RndMtlClose( VOID );
 
INT VE7_RndMtlAdd( ve7MATERIAL *Mtl );

UINT VE7_RndMtlApply( INT MtlNo );

#endif /* __rndres_h_ */
