#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here
  unsigned long i,j,out;

  for (i=0; i<= row; ++i)
  {
      out = 1;
      for (j=1; j<=i; ++j)
      {
          out = (out * (row + 1 - j)) / j;
      }
      printf("%lu", out);
      printf(" ");
  }
  return 0;
}
