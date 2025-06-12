/* FILE NAME  : rndbase.c
 * PROGRAMMER : VE7
 * LAST UPDATE: 09.06.2025
 * PURPOSE    : 3D animation project.
 *          Common declaration module.
 */

#pragma comment(lib, "opengl32")

#include "rnd.h"
#include "time.h"

#include <wglew.h>
#include <gl/wglext.h>

VOID VE7_RndInit( HWND hWnd )
{
  INT i, num;
  HGLRC hRC;
  PIXELFORMATDESCRIPTOR pfd = {0};
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                                  /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
    0
  };
 
  /* Store window handle */
  VE7_hRndWnd = hWnd;
 
  /* Get window DC */
  VE7_hRndDC = GetDC(hWnd);
 
  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(VE7_hRndDC, &pfd);
  DescribePixelFormat(VE7_hRndDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  SetPixelFormat(VE7_hRndDC, i, &pfd);
 
  /* OpenGL init: setup rendering context */
  VE7_hRndGLRC = wglCreateContext(VE7_hRndDC);
  wglMakeCurrent(VE7_hRndDC, VE7_hRndGLRC);
 
  /* Initializing GLEW library */
  if (glewInit() != GLEW_OK)
  {
    MessageBox(VE7_hRndWnd, "Error extensions initializing", "Error", MB_ICONERROR | MB_OK);
    exit(0);
  }
 
  /* Enable a new OpenGL profile support */
  wglChoosePixelFormatARB(VE7_hRndDC, PixelAttribs, NULL, 1, &i, &num);
  hRC = wglCreateContextAttribsARB(VE7_hRndDC, NULL, ContextAttribs);
 
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(VE7_hRndGLRC);
 
  VE7_hRndGLRC = hRC;
  wglMakeCurrent(VE7_hRndDC, VE7_hRndGLRC);

  #ifndef NDEBUG
  OutputDebugString(glGetString(GL_VERSION));
  OutputDebugString("\n");
  OutputDebugString(glGetString(GL_VENDOR));
  OutputDebugString("\n");
  OutputDebugString(glGetString(GL_RENDERER));
  OutputDebugString("\n");

  printf("Version : %s\n", glGetString(GL_VERSION));
  printf("Vendor  : %s\n", glGetString(GL_VENDOR));
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  #endif /* NDEBUG */

  #ifndef NDEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(glDebugOutput, NULL);
  #endif /* NDEBUG */


  glEnable(GL_DEPTH_TEST);

  VE7_RndResize(30, 30);
  VE7_RndCamSet(VecSet1(24), VecSet(0, 0, 0), VecSet(0, 1, 0));
}

VOID VE7_RndClose( VOID )
{
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(VE7_hRndGLRC);
  ReleaseDC(VE7_hRndWnd, VE7_hRndDC);
}

VOID VE7_RndResize( INT W, INT H )
{

  glViewport(0, 0, W, H);
 
  /* Setup projection */
  VE7_RndFrameW = W;
  VE7_RndFrameH = H;
  VE7_RndProjSet();
}

VOID VE7_RndCopyFrame( VOID )
{
  SwapBuffers(VE7_hRndDC);
}

VOID VE7_RndStart( VOID )
{
  FLT ClearColor[4] = {0.30, 0.47, 0.8, 1};
  FLT DepthClearValue = 1;
 
  /* Clear frame */
  glClearBufferfv(GL_COLOR, 0, ClearColor);
  glClearBufferfv(GL_DEPTH, 0, &DepthClearValue);

}

VOID VE7_RndEnd( VOID )
{
  glFinish();
}

VOID VE7_RndProjSet( VOID )
{
  DBL rx, ry;
 
  rx = ry = VE7_RndProjSize;
  if (VE7_RndFrameW > VE7_RndFrameH)
    rx *= (DBL)VE7_RndFrameW / VE7_RndFrameH;
  else
    ry *= (DBL)VE7_RndFrameH / VE7_RndFrameW;
 
  VE7_RndMatrProj = MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2, VE7_RndProjDist, VE7_RndProjFarClip);
  VE7_RndMatrVP = MatrMulMatr(VE7_RndMatrView, VE7_RndMatrProj);
}

VOID VE7_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  VE7_RndMatrView = MatrView(Loc, At, Up);
  VE7_RndMatrVP = MatrMulMatr(VE7_RndMatrView, VE7_RndMatrProj);
}
