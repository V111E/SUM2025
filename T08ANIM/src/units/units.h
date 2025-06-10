/* FILE NAME  : units.h
 * PROGRAMMER : VE7
 * LAST UPDATE: 10.06.2025
 * PURPOSE    : 3D animation project.
 */

#ifndef __units_h_
#define __units_h_

#include rnd/rnd.h

static VOID VE7_UnitInit( ve7UNIT *Uni, ve7ANIM *Ani );
static VOID VE7_UnitClose( ve7UNIT *Uni, ve7ANIM *Ani );
static VOID VE7_UnitResponse( ve7UNIT *Uni, ve7ANIM *Ani );
static VOID VE7_UnitRender( ve7UNIT *Uni, ve7ANIM *Ani );

#endif /* __units_h_ */
