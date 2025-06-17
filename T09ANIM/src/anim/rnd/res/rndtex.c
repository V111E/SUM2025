/* FILE NAME  : rndtex.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 14.06.2025
 * PURPOSE    : 3D animation project.
 */

#include "anim\rnd\rnd.h"

#include <time.h>
#include <stdio.h>
#include <string.h>
                                     
ve7TEXTURE VE7_RndTextures[VE7_MAX_TEXTURES];
INT VE7_RndTexturesSize;


INT VE7_RndTexAddImg( CHAR *Name, INT w, INT h, INT C, VOID *ImageData )
{
  INT mips;

  if (VE7_RndTexturesSize >= VE7_MAX_TEXTURES)
    return -1;

  glGenTextures(1, &VE7_RndTextures[VE7_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, VE7_RndTextures[VE7_RndTexturesSize].TexId);
  mips = log(w > h ? w : h) / log(2);
  mips = mips < 1 ? 1 : mips;
  glTexStorage2D(GL_TEXTURE_2D, mips, C == 4 ? GL_RGBA8 : C == 3 ? GL_RGB8 : GL_R8, w, h);

  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, C == 4 ? GL_BGRA : C == 3 ? GL_BGR : GL_RED, GL_UNSIGNED_BYTE, ImageData);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  strncpy(VE7_RndTextures[VE7_RndTexturesSize].Name, Name, VE7_STR_MAX - 1);
  VE7_RndTextures[VE7_RndTexturesSize].H = h;
  VE7_RndTextures[VE7_RndTexturesSize].W = w;
  glBindTexture(GL_TEXTURE_2D, 0);

  return VE7_RndTexturesSize++;
}

INT VE7_RndTexAddFromFile( CHAR *FileName )
{
  HBITMAP hBm;
  INT TexNo;

  if ((hBm = LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)) != NULL)
  {
    BITMAP bm;
 
    GetObject(hBm, sizeof(bm), &bm);
    TexNo = VE7_RndTexAddImg(FileName, bm.bmWidth, bm.bmHeight, bm.bmBitsPixel / 8, bm.bmBits);
    DeleteObject(hBm);
  }

  return TexNo;
}

VOID VE7_RndTexInit( VOID )
{
  VE7_RndTexturesSize = 0;
}

VOID VE7_RndTexClose( VOID )
{
  INT i;

  for (i = 0; i < VE7_RndTexturesSize; i++)
    glDeleteTextures(1, &VE7_RndTextures[i].TexId);
  VE7_RndTexturesSize = 0;
}


/*End of file*/





