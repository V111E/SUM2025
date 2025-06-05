/* FILE NAME: t06detg.c
 * PROGRAMMER: VE7
 * DATE: 05.06.2025
 * PURPOSE: Do task.
 */

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <windows.h>

typedef DOUBLE DBL;
#define MAX 10

DBL A[MAX][MAX];
INT N;

BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;
 
  N = 0;
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;
  fscanf(F, "%d", &N);
  if (N > MAX)
    N = MAX;
  else
    if (N < 0)
      N = 0;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &A[i][j]);
  fclose(F);
  return TRUE;
}

VOID Swap( DBL *A, DBL *B )
{
  DBL tmp = *A;

  *A = *B;
  *B = tmp;
}


DBL Deteval( INT N )
{
  INT i, y, x, max_row, max_col, j;
  DBL coef;
  DBL Det = 1;

  for (i = 0; i < N; i++)
  {
    max_row = max_col = i;
    for (y = i; y < N; y++)
      for (x = i; x < N; x++)
        if (fabs(A[y][x]) > fabs(A[max_row][max_col]))
           max_row = y, max_col = x;
    if (A[max_row][max_col] == 0)
    {
      Det = 0;
      break;
    }
    if (max_row != i)
    {
      for (x = i; x < N; x++)
        Swap(&A[i][x], &A[max_row][x]);
      Det = -Det;
    }
   
    if (max_col != i)
    {
      for (y = 0; y < N; y++)
        Swap(&A[y][i], &A[y][max_col]);
      Det = -Det;
    }
    for (j = i + 1; j < N; j++)
    {
      coef = A[j][i] / A[i][i];
      A[j][i] = 0;
      for (x = i + 1; x < N; x++)
        A[j][x] -= A[i][x] * coef;
    }
    Det *= A[i][i];
  }

  return Det;
}

VOID main( VOID )
{
  LoadMatrix("MAT2.TXT");
  
  printf("Det = %lf", Deteval(N));
  _getch();
  
}

