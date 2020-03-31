#include "game.h"

/*
This program simulates 2048, a game that I play a lot on long plane rides.
make_game initializes a game and sets the rows and columns according to passed
in parameters, and the score is set to 0. All elements of the board are set to
-1 (empty) and a pointer to the game is returned. remake_game works similarly,
it takes the current board pointer and sets the rows and columns, according to
passed in parameters and sets the score to 0, but doesn't return anything.
All the move functions (move_w, move_a, move_s, and move_d) work similarly.
They iterate through the board by rows/cols or cols/rows depending on the
function, and finds the first available empty spot for each element. They then
swap the values of the cells and sets a change flag to true. It then combines
with the cell adjacent to it if that cell hasn't been combined. The original
cell is set to empty and is ready for the next iteration. If the change flag
has been set, then they return 1. If not, they return 0. get_cell works by
checking if the provided row and column are in range, and then returning a
pointer to the element there. If not, it returns NULL. legal_move_check works
by iterating through the board and returning 1 if there are any empty cells
or if any cell adjacent to the current one has the same value as the current
one. If none of these conditions are met, legal_move_check returns 0. 

partner: pranay2
*/

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    (*mygame).rows = rows;
    (*mygame).cols = cols;
    (*mygame).score = 0;
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            (*mygame).cells[(i * cols) + j] = -1;
        }
    }

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
    (**_cur_game_ptr).rows = new_rows;
    (**_cur_game_ptr).cols = new_cols;
    (**_cur_game_ptr).score = 0;
    int i, j;
    for (i = 0; i < new_rows; i++) {
        for (j = 0; j < new_cols; j++) {
            (**_cur_game_ptr).cells[(i * new_cols) + j] = -1;
        }
    }
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE

    if ((0 <= row && row <= (*cur_game).rows) && (0 <= col && col <= (*cur_game).cols)) { //if in range
        return (*cur_game).cells + (row * (*cur_game).cols + col); //return pointer to cell
    }

    return NULL; //if not in range, return NULL
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
    int i, j; //iterators - col and row
    bool boardFlag = false; //boardFlag detects if something has been moved or combined
    int targetRow = -1; //first available empty location before current row
    int lastCombined = -1; //last combined row
    bool emptyFound = false; //true when there's an empty cell before current row
    int numCols = (*cur_game).cols; //i don't want to type this out every time

    for (i = 0; i < (*cur_game).cols; i++) {
        lastCombined = -1; //resest lastCombined each column
        for (j = 0; j < (*cur_game).rows; j++) {
            int *valAtij = &(*cur_game).cells[(j * numCols) + i];
            if (*valAtij == -1) continue; //skip iteration if row j at col i is empty
            emptyFound = false; //reset emptyFound
            for (targetRow = 0; targetRow < j; targetRow++) {
                if ((*cur_game).cells[(targetRow * numCols) + i] == -1) {
                    emptyFound = true; //if empty location found before current row, set emptyFound flag and break
                    break;
                }
            }
            int *targetVal = &(*cur_game).cells[(targetRow * numCols) + i]; //pointer because i'm lazy
            if (emptyFound) { 
                *targetVal = *valAtij; //switch values if there's an empty spot to switch with
                *valAtij = -1;
                boardFlag = true; //indicate something changed
            }
            int *beforeTargetVal = &(*cur_game).cells[((targetRow - 1) * numCols) + i]; //pointer 2 because i'm lazy
            if ((targetRow - 1) != lastCombined && *beforeTargetVal == *targetVal) { //if previous row hasn't been combined and if same val
                *beforeTargetVal *= 2; //set the first block to double its value
                (*cur_game).score += *beforeTargetVal; //update score
                *targetVal = -1; //make second block empty
                lastCombined = targetRow - 1; //update lastCombined
                boardFlag = true; //indicate something changed
            }
        }
    }
    if (!boardFlag) return 0; //return 0 if nothing changed, if not return 1
    return 1;
}

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int i, j; //iterators - col and row
    bool boardFlag = false; //boardFlag detects if something has been moved or combined
    int targetRow = -1; //first available empty location before current row
    int lastCombined = -1; //last combined row
    bool emptyFound = false; //true when there's an empty cell before current row
    int numCols = (*cur_game).cols; //i don't want to type this out every time

    for (i = 0; i < (*cur_game).cols; i++) {
        lastCombined = -1; //resest lastCombined each column
        for (j = (*cur_game).rows - 1; j > -1; j--) {
            int *valAtij = &(*cur_game).cells[(j * numCols) + i];
            if (*valAtij == -1) continue; //skip iteration if row j at col i is empty
            emptyFound = false; //reset emptyFound
            for (targetRow = (*cur_game).rows - 1; targetRow > j; targetRow--) {
                if ((*cur_game).cells[(targetRow * numCols) + i] == -1) {
                    emptyFound = true; //if empty location found after current row, set emptyFound flag and break
                    break;
                }
            }
            int *targetVal = &(*cur_game).cells[(targetRow * numCols) + i]; //pointer because i'm lazy
            if (emptyFound) { 
                *targetVal = *valAtij; //switch values if there's an empty spot to switch with
                *valAtij = -1;
                boardFlag = true; //indicate something changed
            }
            int *afterTargetVal = &(*cur_game).cells[((targetRow + 1) * numCols) + i]; //pointer 2 because i'm lazy
            if ((targetRow + 1) != lastCombined && *afterTargetVal == *targetVal) { //if previous row hasn't been combined and if same val
                *afterTargetVal *= 2; //set the first block to double its value
                (*cur_game).score += *afterTargetVal; //update score
                *targetVal = -1; //make second block empty
                lastCombined = targetRow + 1; //update lastCombined
                boardFlag = true; //indicate something changed
            }
        }
    }
    if (!boardFlag) return 0; //return 0 if nothing changed, if not return 1
    return 1;
}

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int i, j; //iterators - row and col
    bool boardFlag = false; //boardFlag detects if something has been moved or combined
    int targetCol = -1; //first available empty location before current col
    int lastCombined = -1; //last combined col
    bool emptyFound = false; //true when there's an empty cell before current col
    int numCols = (*cur_game).cols; //i don't want to type this out every time

    for (i = 0; i < (*cur_game).rows; i++) {
        lastCombined = -1; //resest lastCombined each row
        for (j = 0; j < (*cur_game).cols; j++) {
            int *valAtij = &(*cur_game).cells[(i * numCols) + j];
            if (*valAtij == -1) continue; //skip iteration if col j at row i is empty
            emptyFound = false; //reset emptyFound
            for (targetCol = 0; targetCol < j; targetCol++) {
                if ((*cur_game).cells[(i * numCols) + targetCol] == -1) {
                    emptyFound = true; //if empty location found before current col, set emptyFound flag and break
                    break;
                }
            }
            int *targetVal = &(*cur_game).cells[(i * numCols) + targetCol]; //pointer because i'm lazy
            if (emptyFound) { 
                *targetVal = *valAtij; //switch values if there's an empty spot to switch with
                *valAtij = -1;
                boardFlag = true; //indicate something changed
            }
            int *beforeTargetVal = &(*cur_game).cells[(i * numCols) + targetCol - 1]; //pointer 2 because i'm lazy
            if ((targetCol - 1) != lastCombined && *beforeTargetVal == *targetVal) { //if previous col hasn't been combined and if same val
                int curIndex = (i * numCols) + targetCol;
                int prevIndex = (i * numCols) + targetCol - 1;
                if ((curIndex / numCols) == (prevIndex / numCols)) { //if in the same row
                    *beforeTargetVal *= 2; //set the first block to double its value
                    (*cur_game).score += *beforeTargetVal; //update score
                    *targetVal = -1; //make second block empty
                    lastCombined = targetCol - 1; //update lastCombined
                    boardFlag = true; //indicate something changed
                }
            }
        }
    }
    if (!boardFlag) return 0; //return 0 if nothing changed, if not return 1
    return 1;
}

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int i, j; //iterators - row and col
    bool boardFlag = false; //boardFlag detects if something has been moved or combined
    int targetCol = -1; //last available empty location after current col
    int lastCombined = -1; //last combined col
    bool emptyFound = false; //true when there's an empty cell after current col
    int numCols = (*cur_game).cols; //i don't want to type this out every time

    for (i = 0; i < (*cur_game).rows; i++) {
        lastCombined = -1; //resest lastCombined each row
        for (j = (*cur_game).cols - 1; j > -1; j--) {
            int *valAtij = &(*cur_game).cells[(i * numCols) + j];
            if (*valAtij == -1) continue; //skip iteration if col j at row i is empty
            emptyFound = false; //reset emptyFound
            for (targetCol = (*cur_game).cols - 1; targetCol > j; targetCol--) {
                if ((*cur_game).cells[(i * numCols) + targetCol] == -1) {
                    emptyFound = true; //if empty location found after current col, set emptyFound flag and break
                    break;
                }
            }
            int *targetVal = &(*cur_game).cells[(i * numCols) + targetCol]; //pointer because i'm lazy
            if (emptyFound) { 
                *targetVal = *valAtij; //switch values if there's an empty spot to switch with
                *valAtij = -1;
                boardFlag = true; //indicate something changed
            }
            int *afterTargetVal = &(*cur_game).cells[(i * numCols) + targetCol + 1]; //pointer 2 because i'm lazy
            if ((targetCol + 1) != lastCombined && *afterTargetVal == *targetVal) { //if previous col hasn't been combined and if same val
                int curIndex = (i * numCols) + targetCol;
                int nextIndex = (i * numCols) + targetCol + 1;
                if ((curIndex / numCols) == (nextIndex / numCols)) { //if in the same row
                    *afterTargetVal *= 2; //set the first block to double its value
                    (*cur_game).score += *afterTargetVal; //update score
                    *targetVal = -1; //make second block empty
                    lastCombined = targetCol + 1; //update lastCombined
                    boardFlag = true; //indicate something changed
                }
            }
        }
    }
    if (!boardFlag) return 0; //return 0 if nothing changed, if not return 1
    return 1;
}

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    int i, j; //declare iterators
    int numCols = (*cur_game).cols; //variables for rows and cols
    int numRows = (*cur_game).rows;
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            int *valAtij = &(*cur_game).cells[(i * numCols) + j]; //value at [i][j] pointer
            if (*valAtij == -1) return 1; //if empty spaces on board, return 1
            if ((i + 1) < numRows && *valAtij == (*cur_game).cells[((i + 1) * numCols) + j]) return 1; //move_s check
            if ((i - 1) > -1 && *valAtij == (*cur_game).cells[((i -1) * numCols) + j]) return 1; //move_w check
            if ((j + 1) < numCols && *valAtij == (*cur_game).cells[(i * numCols) + j + 1]) { //move_d check
                int curIndex = (i * numCols) + j;
                int nextIndex = (i * numCols) + j + 1;
                if ((curIndex / numCols) == (nextIndex / numCols)) return 1;
            }
            if ((j - 1) > -1 && *valAtij == (*cur_game).cells[(i * numCols) + j + 1]) { //move_a check
                int curIndex = (i * numCols) + j;
                int nextIndex = (i * numCols) + j + 1;
                if ((curIndex / numCols) == (nextIndex / numCols)) return 1;
            }
        }
    }
    return 0; //if none of those work, there are no legal moves
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
