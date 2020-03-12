#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

/*
This program solves a sudoku board. The first function, is_val_in_row, checks
if a specified value is in a given row of the sudoku board. This is done by iterating
through all of the columns for the board at that row and comparing them against the value. 
If the value exists in the row, it returns 1; if not, it returns 0. Similarly, is_val_in_col
checks if a specified value is in a given column of the sudoku board by iterating through
all of the rows of the board at that column and comparing them against the value. If it exists
in the column, it returns 1, and it returns 0 if not. is_val_in_3x3_zone works checks if a specified
value is in a 3x3 section that contains a certain index. It first calculates the row of the first element
in the section by taking the floor of i/3 and then multiplying that by 3. This gets results in either 0, 3,
or 6. It calculates the column of the element using the same method, replacing j for i. It then iterates through
3 rows and columns from the first element and checking if the specified value exists somewhere there, returning 1
if it does and 0 if it does not. is_val_valid works by checking the outputs of is_val_in_row, is_val_in_col, and
is_val_in_3x3_zone - if any of those are 1, the function returns 0. If none of them are 1, the function returns 0.
Finally, solve_sudoku works by iterating through the sudoku board and reuturning 1 if all elements are filled. If
they're not filled, it finds a cell that holds a 0 and tries inputting values 1-9 if valid. If a recursive
call to solve_sudoku solves the board, then it returns 1. If not, the cell will revert to zero and the
function will return 0.

partner: pranay2
*/

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int j; //declare column iteration variable
  for (j = 0; j < 9; j++) { //loop through columns
    if (sudoku[i][j] == val) return 1; // if the value is in any column of the row, return 1
  }
  
  return 0; //if not in the row, return 0
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int i; //declare row iteration variable
  for (i = 0; i < 9; i++) { //loop through rows
    if (sudoku[i][j] == val) return 1; //if the value is in any row of the column, return 1
  }
  
  return 0; //if not in the column, return 0
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  int sectionRow, sectionCol; //declare section variables
  sectionRow = 3 * (i / 3); //calculate the row of the first element in the section the cell is in 
  sectionCol = 3 * (j / 3); //calculate the column of the first element in the section the cell is in 
  
  int row, col; //declare section iteration variables
  for (row = 0; row < 3; row++) {
    for (col = 0; col < 3; col++) { //iterate through section
      if (sudoku[sectionRow + row][sectionCol + col] == val) return 1; //if any element of the section matches the val, return 1
    }
  }
  return 0; //if not in section, return 0


  
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  int rowValid = is_val_in_row(val, i, sudoku); //checks if val is in row
  int colValid = is_val_in_col(val, j, sudoku); //checks if val is in column
  int secValid = is_val_in_3x3_zone(val, i, j, sudoku); //checks if val is in section
  if (rowValid == 1 || colValid == 1 || secValid == 1) return 0; //if any of those, return 0
  return 1; //if none of those, return 1
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i, j, num, unfilledRow, unfilledCol; //declare variables
  int flag = 0; //declare flag for exit condition
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) { //iterate through board
      if (sudoku[i][j] == 0)  {
        flag = 1; //set flag to 1 to indicate board incomplete
        unfilledRow = i; //if 0, record element row
        unfilledCol = j; //if 0, record element column
      }
    }
  }
  if (flag == 0) return 1; //if all filled, return 1

  for (num = 1; num <= 9; num++) { //iterate through possible numbers
    if (sudoku[unfilledRow][unfilledCol] == 0 && is_val_valid(num, unfilledRow, unfilledCol, sudoku) == 1) { //if able to filled
      sudoku[unfilledRow][unfilledCol] = num; //fill cell with number
      if (solve_sudoku(sudoku) == 1) return 1; //recursion 
      sudoku[unfilledRow][unfilledCol] = 0; //if unable to fill, set it back to 0
    }
  }

  return 0; //return 0 for other cases
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}