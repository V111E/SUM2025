/* FILE NAME: t04perm.c
 * PROGRAMMER: VE7
 * DATE: 05.06.2025
 * PURPOSE: Permutation evaluation.
 */

#include <stdio.h>
#include <windows.h>

#define MAX 5
INT P[MAX];
BOOL IsParity;

VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;

  *A = *B;
  *B = tmp;
}

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

VOID Go( INT Pos )
{
  INT i;

  if (Pos == MAX)
    Store();
  else
  {
    for (i = Pos; i < MAX; i++)
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
  INT i;

  for (i = 0; i < MAX; i++)
    P[i] = i + 1;
  Go(0);
}
