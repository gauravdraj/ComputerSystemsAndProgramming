#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*
This program solves mazes uses recursive backracking. Specifically, it utilizes a
Depth First Search to travel as far down a path as possible, and then backtracking
to a different path if it cannot proceed further down the initial one. In doing so
repeatedly, the program can eventually find its way to the end of the maze.

The createMaze funtion takes a pointer to a file as input. After allocating memory for
the maze struct and cells, it copies the maze from a file to the maze. Additionally,
it stores the row and column of where both the start and end of the maze are located.

The destroyMaze function simply frees all the memory allocated for the maze.

The printMaze function iterates through every cell in the maze and prints out its value.

The solveMazeDFS function uses the depth first search to explore possible solutions, 
eventually returning 1 if it can find the end. Additionally, the function marks the
path to the end in the maze, while also marking the different cells it has visited.

partner: pranay2
*/

maze_t * createMaze(char * fileName)
{
    int rows, cols, i, j; //Initialize variables
    char c;
    FILE *mazefile = fopen(fileName, "r"); //Open file
    fscanf(mazefile,"%d %d", &cols, &rows); //Scan column and row values from file to respective variables

    maze_t *newMaze = malloc(sizeof(maze_t)); //Allocate memory for maze struct
    newMaze -> height = rows; //Pass height and width information to maze struct
    newMaze -> width = cols;
    newMaze -> cells = (char**)malloc(rows * sizeof(char*)); //Allocate memory for an array of pointers (cell rows)

    for (i = 0; i < rows; i++) {
        newMaze -> cells[i] = (char*)malloc(cols * sizeof(char)); //Allocate memory for columns in every row
        for (j = 0; j < cols; j++) {
            c = fgetc(mazefile); //Get next character in file
            if (c == '\n') {
                j--; //Character doesn't count if its a newline
                continue;
            }
            newMaze -> cells[i][j] = c; //Copy character to respective maze cell
            if (c == START) //If START is found, store row and column in maze struct
            {
                newMaze -> startRow = i; 
                newMaze -> startColumn = j;
            }
            if (c == END) //If END is found, store row and column in maze struct
            {
                newMaze -> endRow = i;
                newMaze -> endColumn = j;
            }

        }
    }
    fclose (mazefile); //Close file
    return newMaze;
}

void destroyMaze(maze_t * maze)
{
    int i; //Initialize Variables
    for (i=0; i < maze -> height; i++) {
        free (maze -> cells[i]); //Free memory allocated for columns in every row
    }
    free (maze -> cells); //Free memory allocated for row (array of char*)
    free(maze); //Free memory allocated for maze struct
}

void printMaze(maze_t * maze)
{
    int row, col, i, j; //Iniitalize Variables
    row = maze -> height; //Get row and col information from maze struct
    col = maze -> width;

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%c", maze -> cells [i][j]); //Iterate through and print every cell in maze
        }
        printf("\n"); //Print newline at the end of each row
    }
}

int solveMazeDFS(maze_t * maze, int col, int row)
{
    if (row < 0 || col < 0 || row >= maze -> height || col >= maze -> width) return 0; //Return 0 if row/col out of bounds
    if (maze -> cells[row][col] == WALL || maze -> cells[row][col] == PATH || maze -> cells[row][col] == VISITED) return 0; //Return 0 if not empty
    if (maze -> cells[row][col] == END) {
        maze -> cells[maze -> startRow][maze -> startColumn] = START; //Restore maze starting cell back to START value
        return 1; //Return 1 if END is found
    }
    maze -> cells[row][col] = PATH; //Mark current cell as PATH
    if (solveMazeDFS(maze,col-1,row) == 1) return 1; //Check if cell to the left is valid
    if (solveMazeDFS(maze,col+1,row) == 1) return 1; //Check if cell to the right is valid
    if (solveMazeDFS(maze,col,row-1) == 1) return 1; //Check if cell above is valid
    if (solveMazeDFS(maze,col,row+1) == 1) return 1; //Check if cell below is valid
    maze -> cells[row][col] = VISITED; //Mark current cell as VISITED
    return 0;
}