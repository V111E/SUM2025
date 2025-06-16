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
  if (Ani->KeysClick[VK_ESCAPE])
    PostMessage(Ani->hWnd, WM_CLOSE, 0, 0);
  if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;
  if (Ani->KeysClick['W'])
  {
    INT modes[2];

    glGetIntegerv(GL_POLYGON_MODE, modes);
    if (modes[0] == GL_LINE)
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  if (Ani->Keys[VK_CONTROL])
  {
    FLT
      Dist = VecLen(VecSubVec(VE7_RndCamAt, VE7_RndCamLoc)),
      cosT = (VE7_RndCamLoc.Y - VE7_RndCamAt.Y) / Dist,
      sinT = sqrt(1 - cosT * cosT),
      plen = Dist * sinT,
      cosP = (VE7_RndCamLoc.Z - VE7_RndCamAt.Z) / plen,
      sinP = (VE7_RndCamLoc.X - VE7_RndCamAt.X) / plen,
      Azimuth = R2D(atan2(sinP, cosP)),
      Elevator = R2D(atan2(sinT, cosT)),
      sx, sy, Wp, Hp;
    VEC dv;

    Azimuth += Ani->GlobalDeltaTime *
      (-30 * 1 * Ani->Keys[VK_LBUTTON] * Ani->Mdx +
       47 * 1 * (Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]));

    Elevator += Ani->GlobalDeltaTime *
      (-30 * 1 * Ani->Keys[VK_LBUTTON] * Ani->Mdy +
       47 * 1 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]));

    Dist += Ani->GlobalDeltaTime *
      (0.1 * Ani->Mdz +
       8 * 0.1 * (1 + Ani->Keys[VK_SHIFT] * 30) *
          (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR]));
     
    if (Elevator < 0.08)
      Elevator = 0.08;
    if (Elevator > 178)
      Elevator = 178;
    if (Dist < 0.1)
      Dist = 0.1;

    Wp = VE7_RndProjSize;
    Hp = VE7_RndProjSize;
     
    if (Ani->W > Ani->H)
      Wp *= (FLT)Ani->W / Ani->H;
    else
      Hp *= (FLT)Ani->H / Ani->W;
     
    sx = Ani->Keys[VK_RBUTTON] * -Ani->Mdx * Wp / Ani->W * Dist / VE7_RndProjDist;
    sy = Ani->Keys[VK_RBUTTON] * Ani->Mdy * Hp / Ani->H * Dist / VE7_RndProjDist;

    dv = VecAddVec(VecMulNum(VE7_RndCamRight, sx),
                   VecMulNum(VE7_RndCamUp, sy));
    VE7_RndCamAt = VecAddVec(VE7_RndCamAt, dv);
    VE7_RndCamLoc = VecAddVec(VE7_RndCamLoc, dv);
     
    VE7_RndCamSet(PointTransform(VecSet(0, Dist, 0),
                                 MatrMulMatr3(MatrRotateX(Elevator),
                                              MatrRotateY(Azimuth),
                                              MatrTranslate(VE7_RndCamAt))),
                  VE7_RndCamAt,
                  VecSet(0, 1, 0));
  }

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


