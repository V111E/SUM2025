/* FILE NAME  : anim.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 10.06.2025
 * PURPOSE    : 3D animation project.
 */


#ifndef __anim_c_
#define __anim_c_

#include "anim.h"

ve7ANIM VE7_Anim;


VOID VE7_AnimInit( HWND hWnd )
{
  memset(&VE7_Anim, 0, sizeof(ve7ANIM));

  VE7_Anim.hWnd = hWnd;
  VE7_RndInit(hWnd);
  VE7_Anim.hDC = VE7_hRndDC;
  VE7_Anim.W = VE7_RndFrameW;
  VE7_Anim.H = VE7_RndFrameH;

  VE7_TimerInit();

}
VOID VE7_AnimClose( VOID )
{
  INT i;
  for (i = 0; i < VE7_Anim.NumOfUnits; i++)
  {
    VE7_Anim.Units[i]->Close(VE7_Anim.Units[i], &VE7_Anim);
    free(VE7_Anim.Units[i]);
  }
  VE7_RndClose();
  memset(&VE7_Anim, 0, sizeof(ve7ANIM));
}
VOID VE7_AnimResize( INT W, INT H )
{
  VE7_RndResize(W, H);
  VE7_Anim.W = W;
  VE7_Anim.H = H;
}
VOID VE7_AnimCopyFrame( VOID )
{
  VE7_RndCopyFrame();
}
VOID VE7_AnimRender( VOID )
{
  INT i;
  CHAR Buf[100];

  VE7_TimerResponse();

  for (i = 0; i < VE7_Anim.NumOfUnits; i++)
    VE7_Anim.Units[i]->Response(VE7_Anim.Units[i], &VE7_Anim);

  VE7_RndStart();
  for (i = 0; i < VE7_Anim.NumOfUnits; i++)
    VE7_Anim.Units[i]->Render(VE7_Anim.Units[i], &VE7_Anim);
  VE7_RndEnd();
  SetBkMode(VE7_Anim.hDC, TRANSPARENT);
  SetTextColor(VE7_Anim.hDC, RGB(255, 0, 0));
  TextOut(VE7_Anim.hDC, 30, 30, Buf, sprintf(Buf, "FPS = %.5f", VE7_Anim.FPS));

}

VOID VE7_AnimAddUnit( ve7UNIT *Uni )
{
  if (VE7_Anim.NumOfUnits < VE7_MAX_UNITS)
    VE7_Anim.Units[VE7_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &VE7_Anim);
}

VOID VE7_AnimDoExit( VOID )
{
}

#endif /* __anim_c_ */
