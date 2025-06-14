/* FILE NAME  : u_ctrl.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 12.06.2025
 * PURPOSE    : 3D animation project.
 */

#include "units/units.h"

typedef struct
{
  VE7_UNIT_BASE_FIELDS;
} ve7UNIT_CTRL;

static VOID VE7_UnitInit( ve7UNIT_CTRL *Uni, ve7ANIM *Ani )
{
}

static VOID VE7_UnitClose( ve7UNIT_CTRL *Uni, ve7ANIM *Ani)
{
}

static VOID VE7_UnitResponse( ve7UNIT_CTRL *Uni, ve7ANIM *Ani)
{
  if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;

}

static VOID VE7_UnitRender( ve7UNIT_CTRL *Uni, ve7ANIM *Ani)
{
  static CHAR Buf[102];

  sprintf(Buf, "CGSG Animation: FPS = %.5f %s %s %s", Ani->FPS, glGetString(GL_RENDERER), glGetString(GL_VENDOR), glGetString(GL_VERSION));
  SetWindowText(Ani->hWnd, Buf);
}

ve7UNIT * VE7_UnitCreateCTRL( VOID )
{
  ve7UNIT *Uni;

  if ((Uni = VE7_AnimUnitCreate(sizeof(ve7UNIT_CTRL))) == NULL)
    return NULL;
  Uni->Init = (VOID *)VE7_UnitInit;
  Uni->Close = (VOID *)VE7_UnitClose;
  Uni->Response = (VOID *)VE7_UnitResponse;
  Uni->Render = (VOID *)VE7_UnitRender;
  return Uni;
}
