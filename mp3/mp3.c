/* This program prints out a row of Pascal's triangle.
 * The row to print is inputted by the user. Every value 
 * in the row is separated with spaces */

/* Partner: pranay2 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here

  //Initializing variables
  unsigned long i,j,out;
 
  //Loop to print character and space based on calculation
  for (i=0; i<= row; ++i)
  {
      //reset value to 1 at beginning of new row
      out = 1;

      //Loop to calculate value at given row and index
      for (j=1; j<=i; ++j)
      {
          //Formula to calculate value at row and index
          out = (out * (row + 1 - j)) / j;
      }
      //Print value
      printf("%lu", out);

      //Print space
      printf(" ");
  }

  //Program complete
  return 0;
}
