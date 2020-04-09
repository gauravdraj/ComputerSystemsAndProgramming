#include <stdio.h>
#include "slope.h"


// Return index of the first row that is not a slope; otherwise return -1
int find_nonslope_row(int array[6][6]) {
  int i,j;
  int slope = 0;
  for (i = 0; i < 6; i++){
    slope = 0;
    for (j = 0; j < 6; j++) {
      if (j==5) continue;
      if (array[i][j] == array [i][j+1]) return i;
      if (array[i][j] < array [i][j+1] && slope >= 0 ) {
        slope = 1;
      }
      if (array[i][j] < array [i][j+1] && slope < 0 ) {
        return i;
      }
      if (array[i][j] > array [i][j+1] && slope <= 0 ) {
        slope = -1;
      }
      if (array[i][j] > array [i][j+1] && slope > 0 ) {
        return i;
      }
    }
  }
  return -1;
}


int read_array(char* filename, int array[6][6]){
  int i,j,val;
  if (fopen(filename, "r") == NULL) return 0;
  FILE *arrayfile = fopen(filename, "r");
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
      fscanf(arrayfile,"%d",&val);
      array[i][j] = val;
    }
  }
  fclose(arrayfile);
  return 1;
}

