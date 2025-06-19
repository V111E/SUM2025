/* FILE NAME  : u_models.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 17.06.2025
 * PURPOSE    : 3D animation project.
 */

#include <stdio.h>

#include "units.h"

typedef struct tagve7UNIT_MODELS
{
  VE7_UNIT_BASE_FIELDS;
  ve7PRIMS Model;
  VEC Pos;
} ve7UNIT_MODELS;

static VOID VE7_UnitInit( ve7UNIT_MODELS *Uni, ve7ANIM *Ani )
{
  VE7_RndPrimsLoad(&Uni->Model, "bin/models/mersedes.g3dm");
}

static VOID VE7_UnitResponse( ve7UNIT_MODELS *Uni, ve7ANIM *Ani )
{
  Uni->Pos = PointTransform(Uni->Pos, MatrTranslate(VecSet(Ani->Keys['A'] * Ani->GlobalDeltaTime * 15 - Ani->Keys['D'] * Ani->GlobalDeltaTime * 15, 0, 0)));
  Uni->Pos = PointTransform(Uni->Pos, MatrTranslate(VecSet(0, 0, Ani->Keys['W'] * Ani->GlobalDeltaTime * 15 - Ani->Keys['S'] * Ani->GlobalDeltaTime * 15)));
  Uni->Pos = PointTransform(Uni->Pos, MatrTranslate(VecSet(0, Ani->Keys['Y'] * Ani->GlobalDeltaTime * 5 - Ani->Keys['H'] * Ani->GlobalDeltaTime * 5, 0)));

  if (VE7_Anim.LookFor)
    VE7_RndCamSet(VecAddVec(Uni->Pos, VecSet(-20, 90, -20)), Uni->Pos, VecSet(0, 1, 0));
}


static VOID VE7_UnitClose( ve7UNIT_MODELS *Uni, ve7ANIM *Ani)
{
  VE7_RndPrimsFree(&Uni->Model);
}

static VOID VE7_UnitRender( ve7UNIT_MODELS *Uni, ve7ANIM *Ani)
{
  MATR m, p;
  
  p = MatrIdentity();
  p = MatrMulMatr(p, MatrTranslate(VecSet(10, 0, 10)));
  p = MatrMulMatr(p, MatrScale(VecSet1(0.1)));
                       
  m = MatrMulMatr3(MatrRotateY(VE7_Anim.roty / 30),
                   MatrRotateX(VE7_Anim.rotx / 30),
                   MatrRotateZ(0));

  m = MatrMulMatr(m, MatrScale(VecSet1(10)));

  VE7_RndPrimsDraw(&Uni->Model, MatrMulMatr(m, MatrTranslate(Uni->Pos)));
  //VE7_RndPrimsDraw(&Uni->Model, );
}

ve7UNIT * VE7_UnitCreateModels( VOID )
{
  ve7UNIT *Uni;

  if ((Uni = VE7_AnimUnitCreate(sizeof(ve7UNIT_MODELS))) == NULL)
    return NULL;
  Uni->Init = (VOID *)VE7_UnitInit;
  Uni->Close = (VOID *)VE7_UnitClose;
  Uni->Response = (VOID *)VE7_UnitResponse;
  Uni->Render = (VOID *)VE7_UnitRender;
  return Uni;
}
/*End of file*/