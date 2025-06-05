/* FILE NAME: t05det.c
 * PROGRAMMER: VE7
 * DATE: 05.06.2025
 * PURPOSE: Do task.
 */

#include <stdio.h>
#include <conio.h>
#include <windows.h>

typedef DOUBLE DBL;
#define MAX 10

DBL A[MAX][MAX];
INT N;
DBL Det;

INT P[MAX];
BOOL IsParity = TRUE;

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

VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;

  *A = *B;
  *B = tmp;
}

/*
VOID Store ( VOID )
{
  FILE *F;
  INT i;
  
  F = fopen("PERM.TXT", "a");
  if (F == NULL)
    return;
  for (i = 0; i < MAX - 1; i++)
    fprintf(F, "%d, ", P[i]);
  fprintf(F, "%d parity : %s\n", P[MAX - 1], IsParity ? "even" : "odd");
  fclose(F);
}
*/

VOID Go( INT Pos )
{
  INT i;
  DBL prod;

  if (Pos == N)
  {
    for (prod = 1, i = 0; i < N; i++)
      prod *= A[i][P[i]];
    Det += prod * (IsParity * 2 - 1);
  }
  else
  {
    for (i = Pos; i < N; i++)
    {
      if (i != Pos)
        Swap(&P[Pos], &P[i]), IsParity = !IsParity;
      Go(Pos + 1);
      if (i != Pos)
        Swap(&P[Pos], &P[i]), IsParity = !IsParity;
    }
  }
}

void main( void )
{
  int i;

  LoadMatrix("MAT.TXT");

  for (i = 0; i < N; i++)
    P[i] = i;
  Go(0);
  printf("%lf", Det);
  _getch();
  
}

