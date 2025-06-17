/* FILE NAME  : anim.h
 * PROGRAMMER : VE7
 * LAST UPDATE: 10.06.2025
 * PURPOSE    : 3D animation project.
 */

#include "units/units.h"


typedef struct
{
  VE7_UNIT_BASE_FIELDS;
  VEC Pos;
  ve7PRIM Pr;
} ve7UNIT_BALL;

static VOID VE7_UnitInit( ve7UNIT_BALL *Uni, ve7ANIM *Ani )
{
  Uni->Pos = VecSet(0, 1, 0);
  VE7_RndPrimLoad(&Uni->Pr, "bin/models/Mi28.obj");
}

static VOID VE7_UnitClose( ve7UNIT_BALL *Uni, ve7ANIM *Ani)
{
  VE7_RndPrimFree(&Uni->Pr);
}

static VOID VE7_UnitResponse( ve7UNIT_BALL *Uni, ve7ANIM *Ani)
{
  Uni->Pos.X += Ani->DeltaTime * 0.4;

  //if (Ani->KeysClick['P'])
  //  Ani->IsPause = !Ani->IsPause;
  //Uni->CamLoc =
  //  VecAddVec(Uni->CamLoc,
  //    VecMulNum(Uni->CamDir, Ani->GlobalDeltaTime * Uni->Speed *
  //      (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])));
}

static VOID VE7_UnitRender( ve7UNIT_BALL *Uni, ve7ANIM *Ani)
{
  MATR m;
  
  m = MatrMulMatr3(MatrRotateY(VE7_Anim.roty / 30),
                   MatrRotateX(VE7_Anim.rotx / 30),
                   MatrRotateZ(0));
   
  VE7_RndPrimDraw(&Uni->Pr, m);
}

ve7UNIT * VE7_UnitCreateBall( VOID )
{
  ve7UNIT *Uni;

  if ((Uni = VE7_AnimUnitCreate(sizeof(ve7UNIT_BALL))) == NULL)
    return NULL;
  Uni->Init = (VOID *)VE7_UnitInit;
  Uni->Close = (VOID *)VE7_UnitClose;
  Uni->Response = (VOID *)VE7_UnitResponse;
  Uni->Render = (VOID *)VE7_UnitRender;
  return Uni;
}

/*End of file*/