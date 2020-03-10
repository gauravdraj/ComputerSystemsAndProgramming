/*
MP6 is implementing code for the game of life. There are three functions
here, countLiveNeighbor, updateBoard, and aliveStable. countLiveNeighbor
goes through all elements in the row above and below the specified element
(provided that the row and column are in bounds) and increases the number of
alive neighbors if the cell holds a 1. Before returning, it subtracts off the
value of the element itself to get an accurate count. updateBoard uses another
array to keep track of changes to the cells before updating them. It makes the
changes according to the rules set in the MP spec. Once all changes have been
accounted for, it copies the elements of the updated board to the board that was
passed in. aliveStable creates a new array and passes it into updateBoard. It
then compares the contents of the new array against the contents of the passed
in board. If there's any difference, it returns 0. Otherwise, it returns 1.

partner: pranay2
*/

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    int liveNeighbors = 0; //declare + initialize liveNeighbors
    int i, j; //declare loop variables
    for (i = row - 1; i <= row + 1; i++) { //for row above to row below
        if (i >= 0 && i < boardRowSize) { //check if in range
            for (j = col - 1; j <= col + 1; j++) { //for column left to column right
                if (j >= 0 && j < boardColSize) { //check if in range
                    if (board[(i * boardColSize) + j] == 1) { //check if neighbor alive
                        ++liveNeighbors; //increment counter if so
                    }
                }
            }
        }
    }
    liveNeighbors = liveNeighbors - *(board + (row * boardColSize) + col); //subtract element from count
    return liveNeighbors;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {  
    int i, j; //declare loop variables
    int size = boardRowSize * boardColSize; 
    int updatedBoard[size]; //declare array that holds all changes
    int aliveNeighbors = 0; 

    for (i = 0; i < boardRowSize; i++) {
        for (j = 0; j < boardColSize; j++) {
            updatedBoard[(i * boardColSize) + j] = board[(i * boardColSize) + j]; //make sure updated array has all elements
        }
    }
    for (i = 0; i < boardRowSize; i++) {
        for (j = 0; j < boardColSize; j++) { //iterate through board
            aliveNeighbors = countLiveNeighbor(board, boardRowSize, boardColSize, i, j); //get alive neighbors per element
            if (aliveNeighbors < 2) updatedBoard[(i * boardColSize) + j] = 0; //dead if less than 2 neighbors
            else if (aliveNeighbors > 3) updatedBoard[(i * boardColSize) + j] = 0; //dead if more than 3 neighbors
            else if ((aliveNeighbors == 2 || aliveNeighbors == 3) && updatedBoard[(i * boardColSize) + j] == 1) updatedBoard[(i * boardColSize) + j] = 1; //stay alive if 2 or 3 neighbors
            else if (aliveNeighbors == 3 && updatedBoard[(i * boardColSize) + j] == 0) updatedBoard[(i * boardColSize) + j] = 1; //resurrect if 3 neighbors
            else updatedBoard[(i * boardColSize) + j] = 0; //safety case
        }
    }
    for (i = 0; i < boardRowSize; i++) {
        for (j = 0; j < boardColSize; j++) {
            board[(i * boardColSize) + j] = updatedBoard[(i * boardColSize) + j]; //update elements in original board
        }
    } 
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize) {
    int i, j; //declare loop variables
    int size = boardRowSize * boardColSize;
    int updatedBoard[size]; //declare updated array to pass into updateBoard
    for (i = 0; i < boardRowSize; i++) {
        for (j = 0; j < boardColSize; j++) { //iterate through board
            updatedBoard[(i * boardColSize) + j] = *(board + (i * boardColSize) + j); //ensure all elements filled
        }
    }
    updateBoard(updatedBoard, boardRowSize, boardColSize); //get updated board
    for (i = 0; i < boardRowSize; i++) {
        for (j = 0; j < boardColSize; j++) { //iterate through elements
            if (updatedBoard[(i * boardColSize) + j] != *(board + (i * boardColSize) + j)) return 0; //if any changes, return 0
        }
    } 
    return 1; //if no changes, return 1    
}
