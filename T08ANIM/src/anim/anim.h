/* FILE NAME  : anim.h
 * PROGRAMMER : VE7
 * LAST UPDATE: 10.06.2025
 * PURPOSE    : 3D animation project.
 */

#ifndef __anim_h_
#define __anim_h_

#include "rnd/rnd.h"

#define VE7_MAX_UNITS 3000

typedef struct tagve7UNIT ve7UNIT;
typedef struct tagve7ANIM ve7ANIM;

#define VE7_UNIT_BASE_FIELDS \
  VOID (*Init)( ve7UNIT *Uni, ve7ANIM *Ani );     \
  VOID (*Close)( ve7UNIT *Uni, ve7ANIM *Ani );    \
  VOID (*Response)( ve7UNIT *Uni, ve7ANIM *Ani ); \
  VOID (*Render)( ve7UNIT *Uni, ve7ANIM *Ani )

struct tagve7UNIT
{
  VE7_UNIT_BASE_FIELDS;
};

struct tagve7ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;

  ve7UNIT * Units[VE7_MAX_UNITS];
  INT NumOfUnits;

  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                     /* Pause flag */
};

extern ve7ANIM VE7_Anim;

VOID VE7_AnimInit( HWND hWnd );
VOID VE7_AnimClose( VOID );
VOID VE7_AnimResize( INT W, INT H );
VOID VE7_AnimCopyFrame( HDC hDC );
VOID VE7_AnimRender( VOID );      
VOID VE7_AnimAddUnit( ve7UNIT *Uni );
VOID VE7_AnimFlipFullScreen( VOID );
VOID VE7_AnimDoExit( VOID );
VOID VE7_TimerInit( VOID );
VOID VE7_TimerResponce( VOID );


#endif /* __anim_h_ */
