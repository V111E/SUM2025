/* Emelyanov Vasilij */

#include <stdio.h>
#include <windows.h>

void main( void )
{
  int a = 0, b = 100, ans;
  float m;
  char buf[100];

  m = (a + b) / 2;
  while (0 == 0)
  {
    sprintf(buf, "numb > %f?", m);
    ans = MessageBox(NULL, buf, "aiguesser", MB_YESNOCANCEL);
    if (ans == IDYES)
      a = m + 1;
    else if (ans == IDNO)
      b = m - 1;
    else
      break;
    m = (a + b) / 2;
  }
  sprintf(buf, "Answer = %f", m);
  MessageBox(NULL, buf, "aiguesser", MB_OK);
}  


