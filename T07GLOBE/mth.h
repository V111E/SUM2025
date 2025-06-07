#include <math.h>
 
#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)
 
 
/* базовый вещественный тип */
typedef double DBL;
typedef float FLT;
 

/* тип для матрицы - массив в структуре */
typedef struct tagMATR
{
  DBL A[4][4];
} MATR;
 
VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC r = {X, Y, Z};
 
  return r;
}
 
VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
}
 

VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
}


VEC VecMulNum( VEC V, DBL N )
{
  return VecSet(V.X * N, V.Y * N, V.Z * N);
}


VEC VecDivNum( VEC V, DBL N )
{
  return VecSet(V.X / N, V.Y / N, V.Z / N);
}
 
VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}
 
/* скалярное произведение векторов */
DBL VecDotVec( VEC V1, VEC V2 )
{

}
 
/* векторное произведение векторов */
VEC VecCrossVec( VEC V1, VEC V2 )
{

} 

DBL VecLen( VEC V )
{
  DBL len = VecDotVec(V, V);
 
  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}
 
VEC VecNormalize( VEC V )
{
  DBL len = VecDotVec(V, V);
 
  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
}
 
/* преобразования: */
VEC PointTransform( VEC V, MATR M )
{

}

VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
         V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
         V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
}
 
VEC VecMulMatr( VEC V, MATR M )
{
  DBL w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];
 
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
 

MATR MatrIdentity( VOID )
{
  return UnitMatrix;
}

 
MATR MatrSet( DBL A00, DBL A01, DBL A02, DBL A03,
              DBL A10, DBL A11, DBL A12, DBL A13,
              DBL A20, DBL A21, DBL A22, DBL A23,
              DBL A30, DBL A31, DBL A32, DBL A33 )
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
 
MATR MatrTranslate( VEC T )
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
 

MATR MatrScale( VEC S );
MATR MatrRotateX( DBL AngleInDegree );
MATR MatrRotateY( DBL AngleInDegree );
MATR MatrRotateZ( DBL AngleInDegree );
MATR MatrRotate( DBL AngleInDegree, VEC V );
 
MATR MatrMulMatr( MATR M1, MATR M2 )
{
  int i, j, k;
  MATR r = {{{0}}};
 
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (k = 0; k < 4; k++)
        r.A[i][j] += M1.A[i][k] * M2.A[k][j];
}
 
MATR MatrTranspose( MATR M );
 
 
DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                   DBL A21, DBL A22, DBL A23,
                   DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 + A32 - A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
}
 
DBL MatrDeterm( MATR M )
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
 
MATR MatrInverse( MATR M )
{
  DBL det = MatrDeterm(M);
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
}
 
VOID PrintMatrix( CHAR *Text, MATR M )
{
  int i, j;

  if (Text != NULL && Text[0] != 0)
    printf("%s:\n", Text);

  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
      printf(" %12.3", M.A[i][j]);
    printf("\n");
  }
}
 

 
