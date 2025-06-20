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
  VEC B;
  MATR m;
  INT i;

  Uni->Pos = PointTransform(Uni->Pos, MatrTranslate(VecSet(Ani->Keys['A'] * Ani->GlobalDeltaTime * 15 - Ani->Keys['D'] * Ani->GlobalDeltaTime * 15, 0, 0)));
  Uni->Pos = VecAddVec(PointTransform(Uni->Pos, MatrTranslate(VecSet(0, 0, Ani->Keys['W'] * Ani->GlobalDeltaTime * 15 - Ani->Keys['S'] * Ani->GlobalDeltaTime * 15))), VecSet(0, 0, 0)); //Ani->roty * Ani->Keys['W']
  Uni->Pos = PointTransform(Uni->Pos, MatrTranslate(VecSet(0, Ani->Keys['Y'] * Ani->GlobalDeltaTime * 5 - Ani->Keys['H'] * Ani->GlobalDeltaTime * 5, 0)));

  if (Ani->Keys['R'])
  {
    Uni->Pos = VecSet(0, 0, 0);
    VE7_Anim.roty = VE7_Anim.rotx = 0;
  }

  /*
  if (Ani->KeysClick['B'])
  {
    for (i = 0; i < 455; i++)
    {
      B = VecDivNum(VecAddVec(Uni->Model.Prims[i].MaxBB, Uni->Model.Prims[i].MinBB), 2);
      m = MatrMulMatr3(MatrTranslate(VecNeg(B)), , MatrTranslate(B));
      Uni->Model.Prims[i].Trans = m;
    }  
  }
  */
  /*
  if (Ani->Keys['M'])
  {
    B = VecDivNum(VecAddVec(Uni->Model.Prims[451].MaxBB, Uni->Model.Prims[451].MinBB), 2);
    m = MatrMulMatr3(MatrTranslate(VecNeg(B)), MatrRotateZ(45), MatrTranslate(B));
    Uni->Model.Prims[453].Trans = m;
    B = VecDivNum(VecAddVec(Uni->Model.Prims[453].MaxBB, Uni->Model.Prims[453].MinBB), 2);
    m = MatrMulMatr3(MatrTranslate(VecNeg(B)), MatrRotateZ(45), MatrTranslate(B));
    Uni->Model.Prims[453].Trans = m;
  }

  if (Ani->Keys['N'])
  {
    B = VecDivNum(VecAddVec(Uni->Model.Prims[451].MaxBB, Uni->Model.Prims[451].MinBB), 2);
    m = MatrMulMatr3(MatrTranslate(VecNeg(B)), MatrRotateZ(-45), MatrTranslate(B));
    Uni->Model.Prims[453].Trans = m;
    B = VecDivNum(VecAddVec(Uni->Model.Prims[453].MaxBB, Uni->Model.Prims[453].MinBB), 2);
    m = MatrMulMatr3(MatrTranslate(VecNeg(B)), MatrRotateZ(-45), MatrTranslate(B));
    Uni->Model.Prims[453].Trans = m;
  }
  */


  for (i = 439; i < 455; i++)
  {
    B = VecDivNum(VecAddVec(Uni->Model.Prims[i].MaxBB, Uni->Model.Prims[i].MinBB), 2);
    if (Ani->Keys['W'])
      m = MatrMulMatr3(MatrTranslate(VecNeg(B)), MatrRotateX(245 * Ani->Time), MatrTranslate(B));
    else if (Ani->Keys['S'])
      m = MatrMulMatr3(MatrTranslate(VecNeg(B)), MatrRotateX(-245 * Ani->Time), MatrTranslate(B));
    else
      m = MatrMulMatr(MatrTranslate(VecNeg(B)), MatrTranslate(B));
    Uni->Model.Prims[i].Trans = m;
  }

  for (i = 426; i < 429; i++)
  {
    B = VecDivNum(VecAddVec(Uni->Model.Prims[i].MaxBB, Uni->Model.Prims[i].MinBB), 2);
    if (Ani->Keys['W'])
      m = MatrMulMatr3(MatrTranslate(VecNeg(B)), MatrRotateX(245 * Ani->Time), MatrTranslate(B));
    else if (Ani->Keys['S'])
      m = MatrMulMatr3(MatrTranslate(VecNeg(B)), MatrRotateX(-245 * Ani->Time), MatrTranslate(B));
    else
      m = MatrMulMatr(MatrTranslate(VecNeg(B)), MatrTranslate(B));
    Uni->Model.Prims[i].Trans = m;
  }

  //m = MatrMulMatr(MatrTranslate(VecAddVec(VecNeg(Uni->Model.Prims[451].MinBB), VecSet(0, 0 ,0))), MatrScale(VecSet1(1)));

  if (VE7_Anim.LookFor)
    VE7_RndCamSet(VecAddVec(Uni->Pos, VecSet(-40, 90, -40)), Uni->Pos, VecSet(0, 1, 0));


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