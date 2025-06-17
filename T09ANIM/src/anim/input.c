/* FILE NAME  : input.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 12.06.2025
 * PURPOSE    : 3D animation project.
 */

#include "anim.h"


static VOID VE7_AnimKeyboardInit( VOID )
{

}
static VOID VE7_AnimKeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(VE7_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    VE7_Anim.Keys[i] >>= 7;
    VE7_Anim.KeysClick[i] = VE7_Anim.Keys[i] && !VE7_Anim.KeysOld[i];
  }
 
  memcpy(VE7_Anim.KeysOld, VE7_Anim.Keys, 256);

}
static VOID VE7_AnimMouseInit( VOID )
{
}
static VOID VE7_AnimMouseResponse( VOID )
{ 
  POINT pt;
 
  GetCursorPos(&pt);
  ScreenToClient(VE7_Anim.hWnd, &pt);
 
  VE7_Anim.Mdx = pt.x - VE7_Anim.Mx;
  VE7_Anim.Mdy = pt.y - VE7_Anim.My;
  VE7_Anim.Mx = pt.x;
  VE7_Anim.My = pt.y;
} 
static VOID VE7_AnimJoystickInit( VOID )
{
}
static VOID VE7_AnimJoystickResponse( VOID )
{
} 
VOID VE7_AnimInputInit( VOID )
{
  VE7_AnimKeyboardInit();
  VE7_AnimMouseInit();
  VE7_AnimJoystickInit();
}
VOID VE7_AnimInputResponse( VOID )
{
  VE7_AnimKeyboardResponse();
  VE7_AnimMouseResponse();
  VE7_AnimJoystickResponse();

}/*End of file*/