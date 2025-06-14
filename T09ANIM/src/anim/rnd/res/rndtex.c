/* FILE NAME  : rndtex.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 14.06.2025
 * PURPOSE    : 3D animation project.
 */

#include "anim\rnd\rnd.h"

typedef struct tagve7TEXTURE
{
  CHAR Name[VE7_STR_MAX]; /* Texture name */
  INT W, H;               /* Texture size in pixels */
  UINT TexId;             /* OpenGL texture Id */ 
} ve7TEXTURE;

#define VE7_MAX_TEXTURES 3000
ve7TEXTURE VE7_RndTextures[VE7_MAX_TEXTURES];
INT VE7_RndTexturesSize;

VE7_RndTexInit( VOID ); 
VE7_RndTexClose( VOID );

INT VE7_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );

INT VE7_RndTexAdd( CHAR *FileName );








