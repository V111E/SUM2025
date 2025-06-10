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
  VE7_RndInit(hWnd);
}
VOID VE7_AnimClose( VOID )
{
  INT i;
  for (i = 0; i < VE7_Anim.NumOfUnits; i++)
  {
    VE7_Anim.Units[i]->Close(VE7_Anim.Units[i], &VE7_Anim);
    free(VE7_Anim.Units[i]);
    VE7_Anim.Units[i] = NULL;
  }
  VE7_RndClose();
}
VOID VE7_AnimResize( INT W, INT H )
{
  VE7_RndResize(W, H);
  VE7_Anim.W = W;
  VE7_Anim.H = H;
}
VOID VE7_AnimCopyFrame( HDC hDC )
{
  VE7_RndCopyFrame(hDC);
}
VOID VE7_AnimRender( VOID )
{
  INT i;
  VE7_TimerResponce();

  for (i = 0; i < VE7_Anim.NumOfUnits; i++)
    VE7_Anim.Units[i]->Response(VE7_Anim.Units[i], &VE7_Anim);

  VE7_RndStart();
  for (i = 0; i < VE7_Anim.NumOfUnits; i++)
    VE7_Anim.Units[i]->Render(VE7_Anim.Units[i], &VE7_Anim);
  VE7_RndEnd();
}

VOID VE7_AnimAddUnit( ve7UNIT *Uni )
{
  if (VE7_Anim.NumOfUnits < VE7_MAX_UNITS)
    VE7_Anim.Units[VE7_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &VE7_Anim);
}

#endif /* __anim_c_ */
