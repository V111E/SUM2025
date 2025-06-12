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

}
static VOID VE7_AnimMouseInit( VOID )
{
}
static VOID VE7_AnimMouseResponse( VOID )
{ 
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

}