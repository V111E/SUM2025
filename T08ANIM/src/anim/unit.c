/* FILE NAME  : unit.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 10.06.2025
 * PURPOSE    : 3D animation project.
 */
#ifndef __unit_c_
#define __unit_c_

#include "anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ve7UNIT *Uni;
 *   - animation context:
 *       ve7ANIM *Ani;
 * RETURNS: None.
 */
static VOID VE7_UnitInit( ve7UNIT *Uni, ve7ANIM *Ani )
{
} /* End of 'VE7_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ve7UNIT *Uni;
 *   - animation context:
 *       ve7ANIM *Ani;
 * RETURNS: None.
 */
static VOID VE7_UnitClose( ve7UNIT *Uni, ve7ANIM *Ani )
{
} /* End of 'VE7_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ve7UNIT *Uni;
 *   - animation context:
 *       ve7ANIM *Ani;
 * RETURNS: None.
 */
static VOID VE7_UnitResponse( ve7UNIT *Uni, ve7ANIM *Ani )
{
} /* End of 'VE7_UnitResponse' function */
 
/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ve7UNIT *Uni;
 *   - animation context:
 *       ve7ANIM *Ani;
 * RETURNS: None.
 */
static VOID VE7_UnitRender( ve7UNIT *Uni, ve7ANIM *Ani )
{
} /* End of 'VE7_UnitRender' function */
 
/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (ve7UNIT *) pointer to created unit.
 */
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

#endif /* __unit_c_ */
