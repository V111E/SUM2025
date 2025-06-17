/* FILE NAME: mth.h
 * PROGRAMMER: VE7
 * DATE: 09.06.2025
 * PURPOSE: math calc
 */

#ifndef __mth_h_
#define __mth_h_

#include <stdio.h>
#include <math.h>

#include <windows.h>

#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define R2D(A) ((A) * (180.0 / PI))
#define DegRad(a) D2R(a)
#define MatrMulMatr3(A, B, C) MatrMulMatr(MatrMulMatr(A, B), C)
 
/* базовый вещественный тип */
typedef double DBL;
typedef float FLT;
 
typedef struct 
{
  FLT X, Y, Z;
} VEC;

/* тип для матрицы - массив в структуре */
typedef struct tagMATR
{
  FLT A[4][4];
} MATR;

typedef struct tagVEC2
{
  FLT X, Y;
} VEC2;

typedef struct tagVEC4
{
  FLT X, Y, Z, W;
} VEC4;

__inline VEC4 Vec4Set( FLT A, FLT B, FLT C, FLT D )
{
  VEC4 r = {A, B, C, D};
 
  return r;
}

__inline VEC4 Vec4Set1( FLT A )
{
  VEC4 r = {A, A, A, A};
 
  return r;
}

__inline VEC2 Vec2Set( FLT A, FLT B )
{
  VEC2 r = {A, B};
 
  return r;
}

__inline VEC2 Vec2Set1( FLT A )
{
  VEC2 r = {A, A};
 
  return r;
}

__inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC r = {X, Y, Z};
 
  return r;
}

__inline VEC4 Vec4SetVec3w( VEC P, FLT W )
{
  return Vec4Set(P.X, P.Y, P.Z, W);
}

__inline VEC4 Vec4SetVec3( VEC v )
{
  VEC4 v1 = {v.X, v.Y, v.Z, 0};

  return v1;
}
 
__inline VEC VecSet1( FLT A )
{
  VEC r = {A, A, A};
 
  return r;
}
 
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
}
 

__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
}

__inline VEC VecMulNum( VEC V, FLT N )
{
  return VecSet(V.X * N, V.Y * N, V.Z * N);
}

__inline VEC VecDivNum( VEC V, FLT N )
{
  return VecSet(V.X / N, V.Y / N, V.Z / N);
}
 
__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}
 
__inline FLT VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
}

__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
}

__inline FLT VecLen( VEC V )
{
  FLT len = VecDotVec(V, V);
 
  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}

__inline FLT VecLen2( VEC V )
{
  return VecLen( V ) * VecLen( V );
}

__inline VEC VecNormalize( VEC V )
{
  FLT len = VecDotVec(V, V);
 
  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
}
__inline VEC VecMinVec( VEC V1, VEC V2)
{
  return VecSet(V1.X < V2.X ? V1.X : V2.X,
                V1.Y < V2.Y ? V1.Y : V2.Y,
                V1.Z < V2.Z ? V1.Z : V2.Z);
}

__inline VEC VecMaxVec( VEC V1, VEC V2)
{
  return VecSet(V1.X > V2.X ? V1.X : V2.X,
                V1.Y > V2.Y ? V1.Y : V2.Y,
                V1.Z > V2.Z ? V1.Z : V2.Z);
}

 
__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0],
         V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1],
         V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]); 
}

__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
         V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
         V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
}
 
__inline VEC VecMulMatr( VEC V, MATR M )
{
  FLT w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];
 
  return
    VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
         (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
         (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
}

#define VecAddVec3(A, B, C) VecAddVec(A, VecAddVec(B, C))
#define VecAddVec4(A, B, C, В) VecAddVec(VecAddVec(A, B), VecAddVec(C, D))
 
static MATR UnitMatrix = 
{                  
  {                
    {1, 0, 0, 0},  
    {0, 1, 0, 0},  
    {0, 0, 1, 0},  
    {0, 0, 0, 1}   
  }                
};
 
__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
}

__inline MATR MatrSet( FLT A00, FLT A01, FLT A02, FLT A03,
              FLT A10, FLT A11, FLT A12, FLT A13,
              FLT A20, FLT A21, FLT A22, FLT A23,
              FLT A30, FLT A31, FLT A32, FLT A33 )
{
  MATR m =
  {
    {
      {A00, A01, A02, A03},
      {A10, A11, A12, A13},
      {A20, A21, A22, A23},
      {A30, A31, A32, A33},
    }
  };
 
  return m;
}
 
__inline MATR MatrTranslate( VEC T )
{
  MATR m =
  {
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {T.X, T.Y, T.Z, 1}
    }
  };
 
  return m;
}

__inline MATR MatrScale( VEC S )
{
  return MatrSet(S.X, 0, 0, 0,
                 0, S.Y, 0, 0,
                 0, 0, S.Z, 0,
                 0, 0, 0, 1);
}


__inline MATR MatrRotateX( FLT AngleInDegree )
{
  FLT a;

  a = DegRad(AngleInDegree);
  return MatrSet(1, 0, 0, 0,
                 0, cos(a), sin(a), 0,
                 0, -sin(a), cos(a), 0,
                 0, 0, 0, 1);
}

__inline MATR MatrRotateY( FLT AngleInDegree )
{
  FLT a;

  a = DegRad(AngleInDegree);
  return MatrSet(cos(a), 0, -sin(a), 0,
                 0, 1, 0, 0,
                 sin(a), 0, cos(a), 0,
                 0, 0, 0, 1);
}
__inline MATR MatrRotateZ( FLT AngleInDegree )
{
  FLT a;

  a = DegRad(AngleInDegree);
  return MatrSet(cos(a), sin(a), 0, 0,
                 -sin(a), cos(a), 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1);
}
__inline MATR MatrRotate( FLT AngleInDegree, VEC V )
{
  FLT a = DegRad(AngleInDegree), s = sin(a), c = cos(a);
}

__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));
  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };
  return m;
}
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR r = {{{0}}};
  INT i, j, k;
 
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (k = 0; k < 4; k++)
        r.A[i][j] += M1.A[i][k] * M2.A[k][j];
  return r;
}


__inline MATR MatrTranspose( MATR M )
{
  MATR r;
  INT i, j;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      r.A[i][j] = M.A[j][i];
  return r;
}

__inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                   FLT A21, FLT A22, FLT A23,
                   FLT A31, FLT A32, FLT A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 + A32 - A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
}
 
__inline FLT MatrDeterm( MATR M )
{
  return
    M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                              M.A[2][1], M.A[2][2], M.A[2][3],
                              M.A[3][1], M.A[3][2], M.A[3][3]) +
   -M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                              M.A[2][0], M.A[2][2], M.A[2][3],
                              M.A[3][0], M.A[3][2], M.A[3][3]) +
    M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                              M.A[2][0], M.A[2][1], M.A[2][3],
                              M.A[3][0], M.A[3][1], M.A[3][3]) +
   -M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                              M.A[2][0], M.A[2][1], M.A[2][2],
                              M.A[3][0], M.A[3][1], M.A[3][2]);
}

__inline MATR MatrFrustum( FLT l, FLT r, FLT b, FLT t, FLT n, FLT f)
{
  return MatrSet(2 * n / (r - l), 0, 0, 0,
                 0, 2 * n / (t - b), 0, 0,
                 (r + l) / (r - l), (t + b) / (t - b), (f + n) / (f - n) * -1, -1,
                 0, 0, -1 * 2 * n * f / (f - n), 0);
}

 
__inline MATR MatrInverse( MATR M )
{
  FLT det = MatrDeterm(M);
  MATR r;
  INT s[2] = {1, -1}, P[][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};
  int i, j;
 
  if (det == 0)
    return MatrIdentity();
 
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      r.A[j][i] = s[(i + j) % 2] *
        MatrDeterm3x3(M.A[P[i][0]][P[j][0]], M.A[P[i][0]][P[j][1]], M.A[P[i][0]][P[j][2]],
                      M.A[P[i][1]][P[j][0]], M.A[P[i][1]][P[j][1]], M.A[P[i][1]][P[j][2]],
                      M.A[P[i][2]][P[j][0]], M.A[P[i][2]][P[j][1]], M.A[P[i][2]][P[j][2]]) / det;
  return r;
}
 
#endif /* __mth_h_ */

/*End of file*/
