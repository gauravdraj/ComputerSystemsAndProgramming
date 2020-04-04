#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    int rows, cols;
    FILE *mazefile = fopen(fileName, "r");
    fscanf(mazefile,"%d %d", &cols, &rows);

    maze_t *newMaze = malloc(sizeof(maze_t)); 
    newMaze -> height = rows;
    newMaze -> width = cols;
    newMaze -> cells = (char**)malloc(rows * sizeof(char*));
    
    int i, j;
    char c;
    for (i = 0; i < rows; i++) {
        newMaze -> cells[i] = (char*)malloc(cols * sizeof(char));
        for (j = 0; j < cols; j++) {
            c = fgetc(mazefile);
            if (c == '\n') {
                j--;
                continue;
            }
            newMaze -> cells[i][j] = c;
            if (c == START)
            {
                newMaze -> startRow = i;
                newMaze -> startColumn = j;
            }
            if (c == END)
            {
                newMaze -> endRow = i;
                newMaze -> endColumn = j;
            }

        }
    }
    fclose (mazefile);
    return newMaze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    int i;
    for (i=0; i < maze -> height; i++) {
        free (maze -> cells[i]);
    }
    free (maze -> cells);
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    int row, col, i, j;
    row = maze -> height;
    col = maze -> width;

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%c", maze -> cells [i][j]);
        }
        printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    if (row < 0 || col < 0 || row >= maze -> height || col >= maze -> width) return 0;
    if (maze -> cells[row][col] == WALL || maze -> cells[row][col] == PATH || maze -> cells[row][col] == VISITED) return 0;
    if (maze -> cells[row][col] == END) {
        maze -> cells[maze -> startRow][maze -> startColumn] = START;
        return 1;
    } else maze -> cells[row][col] = PATH;

    if (solveMazeDFS(maze,col-1,row) == 1) return 1;
    if (solveMazeDFS(maze,col+1,row) == 1) return 1;
    if (solveMazeDFS(maze,col,row-1) == 1) return 1;
    if (solveMazeDFS(maze,col,row+1) == 1) return 1;
    if (maze -> cells[row][col] != START) maze -> cells[row][col] = VISITED;

    return 0;
}