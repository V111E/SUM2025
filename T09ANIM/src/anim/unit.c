/* FILE NAME  : unit.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 10.06.2025
 * PURPOSE    : 3D animation project.
 */


#include "anim.h"


static VOID VE7_UnitInit( ve7UNIT *Uni, ve7ANIM *Ani )
{
}

static VOID VE7_UnitClose( ve7UNIT *Uni, ve7ANIM *Ani )
{
}
 
static VOID VE7_UnitResponse( ve7UNIT *Uni, ve7ANIM *Ani )
{
}
 
static VOID VE7_UnitRender( ve7UNIT *Uni, ve7ANIM *Ani )
{
}
ve7UNIT * VE7_AnimUnitCreate( INT Size )
{
  ve7UNIT *Uni;
 
  /* Memory allocation */
  if (Size < sizeof(ve7UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
 
  /* Setup unit methods */
  Uni->Init = VE7_UnitInit;
  Uni->Close = VE7_UnitClose;
  Uni->Response = VE7_UnitResponse;
  Uni->Render = VE7_UnitRender;
 
  return Uni;
} /* End of 'VE7_AnimUnitCreate' function */

